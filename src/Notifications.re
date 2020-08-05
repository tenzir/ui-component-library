open Flexboxgrid;

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
};

[@react.component]
let make =
    (
      ~theme,
      ~notifications: array(Notification.t),
      ~handleDismissal=_ => (),
      ~defaultAnimationTime=400,
    ) => {
  <Row _end=`xs bottom=`xs className=Styles.container>
    <Col xs=12 sm=4 md=3 lg=3>
      <Row start=`xs>
        {notifications
         ->Belt.Array.map(notification => {
             <Notification
               key={notification.id}
               theme
               notification
               handleDismissal
               defaultAnimationTime
             />
           })
         ->React.array}
      </Row>
    </Col>
  </Row>;
};
