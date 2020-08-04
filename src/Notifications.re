open Flexboxgrid;

[@bs.deriving accessors]
type notification = {
  id: string,
  title: string,
  body: option(string),
  action: option((string, unit => unit)),
  timeout: option(int),
};

module Styles = {
  open Css;
  let container =
    style([
      position(`fixed),
      width(100.0->vw),
      height(100.0->vh),
      left(`zero),
      top(`zero),
      pointerEvents(`none),
    ]);

  let notification = theme => {
    let colors = StyleHelpers.colorsFromThemeVariant(Some(theme));
    style([
      padding(0.2->rem),
      pointerEvents(`auto),
      marginRight(0.5->rem),
      marginBottom(0.5->rem),
      boxShadow(
        Shadow.box(
          ~y=`zero,
          ~x=`zero,
          ~spread=2->px,
          ~blur=20->px,
          StyleHelpers.rgbWithAlpha(
            StyleHelpers.darken(15, colors.background),
            0.6,
          ),
        ),
      ),
    ]);
  };

  let title = style([margin(0.5->rem)]);

  let body = style([margin(0.5->rem)]);
};

[@react.component]
let make =
    (~theme, ~notifications: array(notification), ~handleDismissal=_ => ()) => {
  let handleAction = (action, id, _) => {
    handleDismissal(id);
    action();
    ();
  };

  <Row _end=`xs bottom=`xs className=Styles.container>
    <Col xs=12 sm=4 md=3 lg=3>
      <Row start=`xs>
        {notifications
         ->Belt.Array.map(notification => {
             <Card depth=(-1) theme className={Styles.notification(theme)}>
               <h4 className=Styles.title>
                 notification.title->React.string
               </h4>
               <p className=Styles.body>
                 {notification.body
                  ->Belt.Option.getWithDefault("")
                  ->React.string}
               </p>
               {notification.action
                ->Belt.Option.mapWithDefault(<Empty />, ((title, action)) =>
                    <Row _end=`xs>
                      <Button
                        size=ButtonStyles.small
                        onClick={handleAction(action, notification.id)}>
                        title->React.string
                      </Button>
                    </Row>
                  )}
             </Card>
           })
         ->React.array}
      </Row>
    </Col>
  </Row>;
};
