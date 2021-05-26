import React from 'react'
import { make as Textarea } from '../src/Textarea.bs.js'
import { Prism as SyntaxHighlighter } from 'react-syntax-highlighter'
import { okaidia } from 'react-syntax-highlighter/dist/esm/styles/prism'
import { useDarkMode } from 'storybook-dark-mode'
import { make as Card } from '../src/Card.bs.js'
import {
    labeled,
    light,
    dark,
    normal,
    mono,
    valid,
    invalid,
} from '../src/UiTypes.bs'
import { both, horizontal, vertical } from '../src/TextareaStyles.bs'
import { tiny, huge } from '../src/CardStyles.bs'

export default {
    title: 'Textarea',
}

const margin = {
    margin: '1rem',
}

export const textarea = () => {
    const theme = useDarkMode() ? dark : light

    return (
        <div style={margin}>
            <Card theme={theme}>
                <h1>Textarea</h1>

                <h3>Interface</h3>
                <p>
                    As there is the option to have a label, we need to have an
                    id so that we can make that clickable and link the label and
                    the input. We can infer the id from the label, but this may
                    clash. When in doubt, add an id.
                </p>
                <SyntaxHighlighter
                    language="reason"
                    style={okaidia}
                    showLineNumbers
                >
                    {`type Textarea: (
  ~_type: option(string), /* maps to "type", defaults to "text" */
  ~defaultValue: option(string), /* defaults to empty string */
  ~value: option(string),
  ~disabled: option(bool), /* defaults to false */
  ~label: option(UiTypes.labels), /* defaults to "UiTypes.Unlabeled" */
  ~id: option(string), /* the id is used to make labels clickable. This falls back to the label */
  ~validity: option(UiTypes.validation), /* defaults to "UiTypes.Valid" */
  ~variant: option(UiTypes.fontStyle), /* defaults to "UiTypes.Normal" */
  ~width: option(float), /* as a percentage. Defaults to "100.0" */
  ~resize=option(TextareaStyles.resize), /* Defauls to NoResize */
  ~theme: option(UiTypes.theme)
  ~placeholder: option(string) /* defaults to empty string */
  ~onChange=option(React.SyntheticEvent.t->unit),
  ~onBlur=option(React.SyntheticEvent.t->unit),
  ~styles=option(array(Css.rule)),
  ~rows=option(int), /* Defaults to 4 rows */
  ~cols=option(int), /* Defaults to 50 rows */
) => React.element;
`}
                </SyntaxHighlighter>

                <h3>Preview</h3>
                <h4>Custom Width</h4>
                <p>Sizing can either be done via the 'Width' attribute.</p>
                <Textarea
                    label={labeled("I'm a tiny input")}
                    placeholder="Like for a zipcode"
                    width={10.0}
                    theme={theme}
                    variant={normal}
                />
                <Textarea
                    label={labeled("I'm a bit bigger")}
                    placeholder="Like for a name"
                    width={60.0}
                    theme={theme}
                    variant={normal}
                />
                <Textarea
                    label={labeled('If the total width stays under 100%')}
                    placeholder="We stay inline"
                    width={30.0}
                    theme={theme}
                    variant={normal}
                />
                <h4>Custom Height</h4>
                <Textarea
                    label={labeled("I'm not that tall")}
                    placeholder="Only 2 rows"
                    width={50}
                    rows={2}
                    theme={theme}
                    variant={normal}
                />
                <Textarea
                    label={labeled("I'm a bit bigger")}
                    placeholder="10 rows for me"
                    width={50}
                    rows={10}
                    theme={theme}
                    variant={normal}
                />
                <h4>Labeled vs Unlabeled</h4>
                <Textarea
                    label={labeled('I have a label')}
                    placeholder="Check my cool label above"
                    width={50.0}
                    theme={theme}
                    variant={normal}
                />
                <Textarea
                    placeholder="I don't"
                    width={50.0}
                    theme={theme}
                    variant={normal}
                />

                <h4>Normal / Mono fonts</h4>
                <Textarea
                    label={labeled('Normal Font')}
                    placeholder="Font setting will also have effect in the placeholder"
                    width={50.0}
                    theme={theme}
                    variant={normal}
                />
                <Textarea
                    label={labeled('Mono Font')}
                    placeholder="And in the label"
                    width={50.0}
                    theme={theme}
                    variant={mono}
                />

                <h4>Resizeable</h4>
                <Textarea
                    label={labeled("I'm not resizable")}
                    placeholder="Neither horizontally nor vertically"
                    theme={theme}
                />
                <Textarea
                    label={labeled('I can resize')}
                    placeholder="Horizontally only"
                    resize={horizontal}
                    theme={theme}
                />
                <Textarea
                    label={labeled('I can resize')}
                    placeholder="Vertically only"
                    resize={vertical}
                    theme={theme}
                />
                <Textarea
                    label={labeled('I can resize')}
                    placeholder="All the ways"
                    resize={both}
                    theme={theme}
                />
            </Card>
        </div>
    )
}
