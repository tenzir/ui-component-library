import React from 'react'
import { Examples } from '../src/Tooltip.bs'
import { Prism as SyntaxHighlighter } from 'react-syntax-highlighter'
import { okaidia } from 'react-syntax-highlighter/dist/esm/styles/prism'
import { useDarkMode } from 'storybook-dark-mode'
import { FiActivity as Activity } from 'react-icons/fi'
import { make as Card } from '../src/Card.bs.js'
import { light, dark } from '../src/UiTypes.bs'
import { top, right, bottom, left } from '../src/Tooltip.bs'

const TooltipExamples = Examples.make

export default {
    title: 'Tooltip',
}

const margin = {
    margin: '1rem',
}

export const Tooltips = () => {
    const theme = useDarkMode() ? dark : light
    return (
        <>
            <div style={margin}>
                <Card theme={theme}>
                    <h1>Tooltip</h1>
                    <h3>Interface</h3>
                    <SyntaxHighlighter
                        language="reason"
                        style={okaidia}
                        showLineNumbers
                    >
                        {`type tooltip: (
  ~theme: option(UiTypes.theme)), // Defaults to UiTypes.light
  ~position: option(Tooltip.tPosition)), // Defaults to Top(Center)
  value: string
)=> string;`}
                    </SyntaxHighlighter>

                    <p>
                        As opposed to most elements, this is not a component,
                        but a css class generator. Based on the options above,
                        we generate a tooltip that is placed on the "after"
                        attribute of the element. This means we're not adding
                        additional dom. The interface for positioning looks as
                        follows:
                    </p>

                    <SyntaxHighlighter
                        language="reason"
                        style={okaidia}
                        showLineNumbers
                    >
                        {`type horizontal =
  | Left
  | Center
  | Right;

type vertical =
  | Top
  | Middle
  | Bottom;

type tPosition =
  | Top(horizontal)
  | Bottom(horizontal)
  | Left(vertical)
  | Right(vertical);

// For instance,
// Adding a tooltip to the top left or bottom right of an element, would be:
<SomeElement className={tooltip: (
  ~position: Top(Left)),
  value: "Some Tooltip"
)}

<SomeElement className={tooltip: (
  ~position: Bottom(Right)),
  value: "Some Tooltip"
)}
`}
                    </SyntaxHighlighter>

                    <h3>Previews</h3>
                    <TooltipExamples theme={theme} />
                </Card>
            </div>
        </>
    )
}
