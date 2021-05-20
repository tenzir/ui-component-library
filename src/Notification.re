open BsFlexboxgrid;

[@bs.deriving accessors]
type t = {
  id: string,
  title: string,
  body: option(string),
  action: option((string, unit => unit)),
  timeout: option(int),
};

let create =
    (~id=GenericHelpers.v4(), ~body=None, ~action=None, ~timeout=None, title) => {
  id,
  title,
  body,
  action,
  timeout,
};

type state =
  | Entering
  | Stale
  | Leaving;

module Styles = {
  open Css;
  let notification = (theme, state, defaultAnimationTime) => {
    let colors = StyleHelpers.colorsFromThemeVariant(theme);

    let animOut =
      keyframes([
        (0, [transform(translateX(0.0->pct))]),
        (100, [transform(translateX(100.0->pct))]),
      ]);

    let animIn =
      keyframes([
        (0, [transform(translateX(100.0->pct))]),
        (100, [transform(translateX(0.0->pct))]),
      ]);

    let animation = (state, defaultAnimationTime) =>
      switch (state) {
      | Entering => [
          animationName(animIn),
          animationDuration(defaultAnimationTime),
          animationTimingFunction(`easeOut),
        ]
      | Leaving => [
          animationName(animOut),
          animationDuration(defaultAnimationTime),
          animationTimingFunction(`easeOut),
        ]
      | _ => [transform(translateX(0.0->pct))]
      };

    style([
      pointerEvents(`auto),
      marginRight(0.5->rem),
      marginBottom(0.5->rem),
      overflow(`visible)->important,
      boxShadow(
        Shadow.box(
          ~y=`zero,
          ~x=`zero,
          ~spread=2->px,
          ~blur=20->px,
          StyleHelpers.rgbWithAlpha(
            switch (theme) {
            | UiTypes.Light => StyleHelpers.darken(15, colors.background)
            | _ => StyleHelpers.darken(5, colors.background)
            },
            0.6,
          ),
        ),
      ),
      hover([selector("& .close-button", [opacity(1.0)])]),
      ...animation(state, defaultAnimationTime),
    ]);
  };

  let closeButton =
    style([
      position(`absolute)->important,
      top((-1.0)->rem),
      left((-1.4)->rem),
      padding4(
        ~top=0.5->rem,
        ~right=0.8->rem,
        ~bottom=0.45->rem,
        ~left=0.8->rem,
      )
      ->important,
      opacity(0.0),
      ...Config.Misc.baseTransitions,
    ]);

  let title = style([margin(0.5->rem)]);
  let body = style([margin(0.5->rem)]);

  let timeout = (theme, timeout, hovered) => {
    let size =
      keyframes([(0, [width(0.0->pct)]), (100, [width(100.0->pct)])]);
    let colors = StyleHelpers.colorsFromThemeVariant(theme);
    style([
      backgroundColor(
        StyleHelpers.rgbWithAlpha(
          StyleHelpers.darken(20, colors.background),
          0.6,
        ),
      ),
      borderRadius(Config.Misc.borderRadius),
      width(100.0->pct),
      height(0.4->rem),
      position(`absolute),
      bottom(`zero),
      left(`zero),
      animationName(size),
      animationDuration(timeout),
      animationTimingFunction(`easeOut),
      animationPlayState(hovered ? `paused : `running),
      opacity(hovered ? 0.0 : 1.0),
      ...Config.Misc.baseTransitions,
    ]);
  };
};

type dismissal =
  | Initial
  | Timeout
  | Forced;

[@react.component]
let make =
    (
      ~theme=Config.defaultTheme,
      ~notification,
      ~handleDismissal,
      ~defaultAnimationTime,
    ) => {
  let (state, setState) = React.useState(_ => Entering);
  let (hovered, setHovered) = React.useState(_ => false);
  let (readyForDismissal, setReadyForDismissal) =
    React.useState(_ => Initial);
  let mounted = React.useRef(false);

  React.useEffect0(_ => {
    mounted.current = true;
    Some(_ => mounted.current = false);
  });

  React.useEffect2(
    () => {
      switch (readyForDismissal, hovered) {
      | (Forced, _)
      | (Timeout, false) =>
        setState(_ => Leaving)->ignore;
        Js.Global.setTimeout(
          () => {handleDismissal(notification.id)},
          defaultAnimationTime,
        )
        ->ignore;
      | _ => ()
      };

      None;
    },
    (hovered, readyForDismissal),
  );

  let handleAction = (action, _) => {
    setReadyForDismissal(_ => Forced);
    action()->ignore;
  };

  <Card
    onMouseOver={_ => setHovered(_ => true)}
    depth={
      switch (theme) {
      | UiTypes.Light => (-1)
      | _ => 1
      }
    }
    theme
    className={Styles.notification(theme, state, defaultAnimationTime)}>
    <Button
      onClick={_ => setReadyForDismissal(_ => Forced)}
      className={"close-button " ++ Styles.closeButton}
      variant=ButtonStyles.Secondary>
      <Icons.X size=18 />
    </Button>
    <h4 className=Styles.title> notification.title->React.string </h4>
    <p className=Styles.body>
      {notification.body->Belt.Option.getWithDefault("")->React.string}
    </p>
    {notification.action
     ->Belt.Option.mapWithDefault(<Empty />, ((title, action)) =>
         <Row _end=`xs>
           <Button size=UiTypes.small onClick={handleAction(action)}>
             title->React.string
           </Button>
         </Row>
       )}
    {notification.timeout
     ->Belt.Option.mapWithDefault(
         <Empty />,
         timeout => {
           if (mounted.current) {
             Js.Global.setTimeout(
               () => setReadyForDismissal(_ => Timeout),
               timeout,
             )
             ->ignore;
           };
           <div className={Styles.timeout(theme, timeout, hovered)}>
             <Empty />
           </div>;
         },
       )}
  </Card>;
};
