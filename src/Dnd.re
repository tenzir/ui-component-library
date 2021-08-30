module Context = {
  type dragItem = {
    droppableId: string,
    index: int,
  };
  type dragEndEvent = {
    destination: Js.Nullable.t(dragItem),
    source: dragItem,
    /*combine: Js.Nullable.t(combine),*/
    /*draggableId: string,*/
    /*mode: string,*/
    /*reason: string,*/
    /*type_: string*/
  };
  type dragStartEvent = {
    source: dragItem,
    /*combine: Js.Nullable.t(combine),*/
    /*draggableId: string,*/
    /*mode: string,*/
    /*reason: string,*/
    /*type_: string*/
  };

  [@bs.module "react-beautiful-dnd"] [@react.component]
  external make:
    (
      ~onDragStart: dragStartEvent => unit=?,
      ~onDragUpdate: ReactEvent.Synthetic.t => unit=?,
      ~onDragEnd: dragEndEvent => unit,
      ~children: React.element=?
    ) =>
    React.element =
    "DragDropContext";
};

module Draggable = {
  [@bs.module "./Dnd.js"] [@react.component]
  external make:
    (
      ~isDragDisabled: bool=?,
      ~draggableId: string,
      ~index: int,
      ~children: React.element=?
    ) =>
    React.element =
    "DraggableWrapper";
};

module Droppable = {
  type direction = [ | `vertical | `horizontal];
  [@bs.module "./Dnd.js"] [@react.component]
  external make:
    (
      ~droppableId: string,
      ~direction: direction=?,
      ~children: React.element=?
    ) =>
    React.element =
    "DroppableWrapper";
};
