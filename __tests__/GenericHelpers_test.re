open Jest;
open Expect;

describe("bound", () => {
  let lowerBound = -10;
  let upperBound = 10;
  let bounded = GenericHelpers.bound(lowerBound, upperBound);

  test("LowerBound", () =>
    expect(bounded(-100)) |> toBe(lowerBound))
  test("UpperBound", () =>
    expect(bounded(100)) |> toBe(upperBound))
  test("Within Bounds", () =>
    expect(bounded(0)) |> toBe(0))

  let lowerBoundFlt = -10.0;
  let upperBoundFlt = 10.0;
  let bounded = GenericHelpers.bound(lowerBoundFlt, upperBoundFlt);

  test("LowerBound Float", () =>
    expect(bounded(-100.0)) |> toBe(lowerBoundFlt))
  test("UpperBound Float", () =>
    expect(bounded(100.0)) |> toBe(upperBoundFlt))
  test("Within Bounds Float", () =>
    expect(bounded(0.0)) |> toBe(0.0))
});

describe("operatePercent", () => {
  let percentage = 10;
  let baseValue = 50;

  test("Add", () =>
    expect(GenericHelpers.operatePercent(percentage, UiTypes.Add, baseValue)) |> toBe(75))

  test("Subtract", () =>
    expect(GenericHelpers.operatePercent(percentage, UiTypes.Subtract, baseValue)) |> toBe(25))
});
