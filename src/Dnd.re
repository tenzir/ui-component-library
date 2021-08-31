module OpaqueTypes = {
  type draggableProps;
  type dragHandleProps;
  type provided = {
    innerRef: ReactDOM.Ref.t,
    placeholder: React.element,
    draggableProps,
    dragHandleProps,
  };
};

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

module Provided = {
  let augmentChildren: (OpaqueTypes.provided, React.element) => React.element = [%bs.raw
    {|
    function (provided, children) {
      return {
        ...children,
        ref: provided.innerRef,
        props: {
            ...children.props,
            ...provided.draggableProps,
            ...provided.dragHandleProps,
        }
     };
    }
  |}
  ];
};

module Draggable = {
  module Wrapper = {
    [@bs.module "react-beautiful-dnd"] [@react.component]
    external make:
      (
        ~isDragDisabled: bool=?,
        ~draggableId: string,
        ~index: int,
        ~children: OpaqueTypes.provided => React.element=?
      ) =>
      React.element =
      "Draggable";
  };

  [@react.component]
  let make = (~draggableId, ~index, ~isDragDisabled, ~children) => {
    <Wrapper draggableId index isDragDisabled>
      {(provided: OpaqueTypes.provided) => {
         <>
           {Provided.augmentChildren(provided, children)}
           {provided.placeholder}
         </>;
       }}
    </Wrapper>;
  };
};

module Droppable = {
  type direction = [ | `vertical | `horizontal];

  module Wrapper = {
    [@bs.module "react-beautiful-dnd"] [@react.component]
    external make:
      (
        ~droppableId: string,
        ~direction: direction=?,
        ~children: OpaqueTypes.provided => React.element=?
      ) =>
      React.element =
      "Droppable";
  };

  [@react.component]
  let make = (~droppableId, ~direction, ~children) => {
    <Wrapper droppableId direction>
      {(provided: OpaqueTypes.provided) => {
         <>
           {Provided.augmentChildren(provided, children)}
           {provided.placeholder}
         </>;
       }}
    </Wrapper>;
  };
};
