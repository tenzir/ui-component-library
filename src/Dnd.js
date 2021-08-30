import React from 'react'
import { Droppable } from 'react-beautiful-dnd'
import { Draggable } from 'react-beautiful-dnd'

const Provided = ({ provided, innerRef, children }) => {
    const augmentedChildren = {
        ...children,
        ref: innerRef,
        props: {
            ...children.props,
            ...provided.draggableProps,
            ...provided.dragHandleProps,
        },
    }
    return (
        <>
            {augmentedChildren}
            {provided.placeholder}
        </>
    )
}

export const DroppableWrapper = ({ direction, droppableId, children }) => {
    const ref = React.useRef()
    return (
        <Droppable droppableId={droppableId} direction={direction}>
            {(provided) => {
                return (
                    <Provided provided={provided} innerRef={provided.innerRef}>
                        {children}
                    </Provided>
                )
            }}
        </Droppable>
    )
}

export const DraggableWrapper = ({ index, draggableId, children }) => {
    const ref = React.useRef()
    return (
        <Draggable draggableId={draggableId} index={index}>
            {(provided) => {
                return (
                    <Provided provided={provided} innerRef={provided.innerRef}>
                        {children}
                    </Provided>
                )
            }}
        </Draggable>
    )
}
