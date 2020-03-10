open Jest;
open StyleHelpers;
open Css;
open Expect;

describe("rgbWithAlpha", () => {
  let supportedColour = `rgb((0, 0, 0));
  let unsupportedColours = [
    ("hex", `hex("000")),
    ("rgba", `rgba((0, 0, 0, 0))),
    ("hsl", `hsl((0.0->deg, [0.0->pct], [0.0->pct]))),
    ("hsla", `hsla((0.0->deg, [0.0->pct], [0.0->pct], [0.0->pct]))),
    ("transparent", `transparent),
    ("currentColor", `currentColor),
  ];

  test("Add an alpha channel to RGB colors", () =>
    expect(rgbWithAlpha(supportedColour, 0))
    |> toEqual(`rgba((0, 0, 0, 0)))
  );

  unsupportedColours
  ->Belt.List.map(colorTuple => {
      let (name, color) = colorTuple;
      test("Not add an alpha channel to " ++ name, () =>
        expect(rgbWithAlpha(color, 0)) |> toEqual(color)
      );
      ();
    })
  ->ignore;
});

describe("mapRGB", () => {
  let rgb = 0;
  let rgbF = 0;
  let fixed = _ => rgbF;

  test("Map", () =>
    expect(mapRGB(fixed, rgb, rgb, rgb)) |> toEqual((rgbF, rgbF, rgbF))
  );
});

describe("applyPercentageToColor", () => {
  let percentage = 10;
  let color = `rgb((50, 50, 50));
  let colorWithAlpha = `rgba((50, 50, 50, 50.0));
  let unsupportedColours = [
    ("hex", `hex("000")),
    ("transparent", `transparent),
    ("currentColor", `currentColor),
  ];

  test("Lighten RGB", () =>
    expect(applyPercentageToColor(UiTypes.Lighten, percentage, color))
    |> toEqual(`rgb((75, 75, 75)))
  );

  test("Darken RGB", () =>
    expect(applyPercentageToColor(UiTypes.Darken, percentage, color))
    |> toEqual(`rgb((25, 25, 25)))
  );

  test(" Lighten RGBA", () =>
    expect(
      applyPercentageToColor(UiTypes.Lighten, percentage, colorWithAlpha),
    )
    |> toEqual(`rgba((75, 75, 75, 50.0)))
  );

  test("Darken RGBA", () =>
    expect(
      applyPercentageToColor(UiTypes.Darken, percentage, colorWithAlpha),
    )
    |> toEqual(`rgba((25, 25, 25, 50.0)))
  );

  unsupportedColours
  ->Belt.List.map(colorTuple => {
      let (name, color) = colorTuple;
      test("Leave unspported colors intact (lighten) -- " ++ name, () =>
        expect(applyPercentageToColor(UiTypes.Lighten, percentage, color))
        |> toEqual(color)
      );
      test("Leave unspported colors intact (darken) -- " ++ name, () =>
        expect(applyPercentageToColor(UiTypes.Darken, percentage, color))
        |> toEqual(color)
      );
      ();
    })
  ->ignore;
});

describe("lighten / darken shorthands", () => {
  let percentage = 10;
  let color = `rgb((50, 50, 50));
  let colorWithAlpha = `rgba((50, 50, 50, 50.0));
  let unsupportedColours = [
    ("hex", `hex("000")),
    ("transparent", `transparent),
    ("currentColor", `currentColor),
  ];

  test("Lighten RGB", () =>
    expect(lighten(percentage, color)) |> toEqual(`rgb((75, 75, 75)))
  );

  test("Darken RGB", () =>
    expect(darken(percentage, color)) |> toEqual(`rgb((25, 25, 25)))
  );

  test("Lighten RGBA", () =>
    expect(lighten(percentage, colorWithAlpha))
    |> toEqual(`rgba((75, 75, 75, 50.0)))
  );

  test("Darken RGBA", () =>
    expect(darken(percentage, colorWithAlpha))
    |> toEqual(`rgba((25, 25, 25, 50.0)))
  );

  unsupportedColours
  ->Belt.List.map(colorTuple => {
      let (name, color) = colorTuple;
      test("Leave unspported colors intact (lighten) -- " ++ name, () =>
        expect(lighten(percentage, color)) |> toEqual(color)
      );
      test("Leave unspported colors intact (darken) -- " ++ name, () =>
        expect(darken(percentage, color)) |> toEqual(color)
      );
      ();
    })
  ->ignore;
});

describe("colorsFromThemeVariant", () => {
  test("Return light theme", () =>
    expect(colorsFromThemeVariant(Some(UiTypes.Light))) |> toEqual(Config.Colors.light)
  );
  test("Return dark theme", () =>
    expect(colorsFromThemeVariant(Some(UiTypes.Dark))) |> toEqual(Config.Colors.dark)
  );
  test("Return tenzir blue theme", () =>
    expect(colorsFromThemeVariant(Some(UiTypes.TenzirBlue))) |> toEqual(Config.Colors.tenzirBlue)
  );
  test("Return default theme", () =>
    expect(colorsFromThemeVariant(None)) |> toEqual(Config.Colors.light)
  );
});
