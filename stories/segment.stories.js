import React from 'react'
import { Prism as SyntaxHighlighter } from 'react-syntax-highlighter'
import { okaidia } from 'react-syntax-highlighter/dist/esm/styles/prism'
import { useDarkMode } from 'storybook-dark-mode'
import { make as Segment } from '../src/Segment.bs.js'
import { FiActivity as Activity } from 'react-icons/fi'
import { make as Card } from '../src/Card.bs.js'
import { light, dark } from '../src/UiTypes.bs'

export default {
    title: 'Segment',
}

const segmentContainer = {
    display: 'inline-block',
    width: '40%',
    marginRight: '100px',
    paddingBottom: '100px',
}
const margin = {
    margin: '1rem',
}

export const Segments = () => {
    const theme = useDarkMode() ? dark : light
    const [value, setValue] = React.useState(0)
    return (
        <div style={margin}>
            <Card depth={0} theme={theme}>
                <h1>Dropdowns</h1>
                <h3>Interface</h3>
                <SyntaxHighlighter
                    language="reason"
                    style={okaidia}
                    showLineNumbers
                >
                    {`type t = {
  disabled: bool,
  id: string,
  title: string,
};

type Dropdown: (
  ~theme: option(UiTypes.theme)
  ~segments: array(t),
  ~default: option(string), /* The id of the item */
  ~onSegmentUpdate: string => unit, /* The changed id get's pushed back */
  ~title: option(string),
) => React.element;
`}
                </SyntaxHighlighter>

                <h3>Preview</h3>
                <div style={segmentContainer}>
                    <p>A regular segment</p>
                    <Segment
                        theme={theme}
                        onSegmentUpdate={() => null}
                        segments={[
                            { title: 'Lorum', id: 0, disabled: false },
                            { title: 'Ipsum', id: 1, disabled: false },
                            { title: 'Dolor', id: 2, disabled: false },
                        ]}
                    />
                </div>
                <div style={segmentContainer}>
                    <p>
                        When specifying disabled elements, we select the first
                        non-disabled element in line by default
                    </p>
                    <Segment
                        theme={theme}
                        onSegmentUpdate={() => null}
                        segments={[
                            { title: 'Lorum', id: 0, disabled: true },
                            { title: 'Ipsum', id: 1, disabled: false },
                            { title: 'Dolor', id: 2, disabled: false },
                        ]}
                    />
                </div>
                <div style={segmentContainer}>
                    <p>
                        You can also specify a default selection. This will be
                        selected upon first render.
                    </p>
                    <Segment
                        theme={theme}
                        default={2}
                        onSegmentUpdate={() => null}
                        segments={[
                            { title: 'Lorum', id: 0, disabled: false },
                            { title: 'Ipsum', id: 1, disabled: false },
                            { title: 'Dolor', id: 2, disabled: false },
                        ]}
                    />
                </div>
            </Card>
        </div>
    )
}
