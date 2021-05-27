import React from 'react'
import { make as Button, Group } from '../src/Button.bs.js'
import { secondary, make as Slider } from '../src/Slider.bs.js'
import { Prism as SyntaxHighlighter } from 'react-syntax-highlighter'
import { okaidia } from 'react-syntax-highlighter/dist/esm/styles/prism'
import { make as Dropdown } from '../src/Dropdown.bs.js'
import { useDarkMode } from 'storybook-dark-mode'
import { FiActivity as Activity } from 'react-icons/fi'
import { make as Card } from '../src/Card.bs.js'
import { light, dark } from '../src/UiTypes.bs'

const ButtonGroup = Group.make
export default {
    title: 'Slider',
}

const margin = {
    margin: '1rem',
}

const heightSpacer = {
    height: '6rem',
}

export const Sliders = () => {
    const theme = useDarkMode() ? dark : light
    const [vals, setVals] = React.useState({
        simple: 50,
        rendered: 50,
        withChild: {
            value: 50,
            unit: 'm',
        },
    })
    return (
        <>
            <div style={margin}>
                <Card theme={theme}>
                    <h1>Sliders</h1>
                    <h3>Interface</h3>
                    <SyntaxHighlighter
                        language="reason"
                        style={okaidia}
                        showLineNumbers
                    >
                        {`type Slider: (
  ~theme: option(UiTypes.theme)),
  ~label: UiTypes.labels, /* defaults to "UiTypes.Unlabeled" */
  ~min:int, /* defaults to 0 */
  ~max:int, /* defaults to 100 */
  ~value: int,
  ~displayValue: string, /* If none is provided, the stringified value will be used */
  ~align: Slider.align, /* Defaults to Left */
  ~font: UiTypes.fontStyle, /* Defaults to Normal */
  ~variant: Slider.variant, /* Defaults to Primary */
  ~id: string,
  ~onChange:React.SyntheticEvent.t->unit,
  ~onInput:React.SyntheticEvent.t->unit,
  ~className:string,
  ~childrenOffset:int /* in px. this wil offset child elements vertically */
  ~children:option(React.Element)
)=> React.element;`}
                    </SyntaxHighlighter>

                    <h3>Previews</h3>
                    <h4>Simple Slider</h4>
                    <Slider
                        id="simple-slider"
                        theme={theme}
                        variant={secondary}
                        value={vals.simple}
                        onChange={(event) =>
                            event.persist() ||
                            setVals((vals) => ({
                                ...vals,
                                simple: event.target.value,
                            }))
                        }
                    ></Slider>
                    <h4>Slider with a rendered value</h4>
                    <Slider
                        id="rendered-slider"
                        theme={theme}
                        variant={secondary}
                        displayValue={vals.rendered + '%'}
                        value={vals.rendered}
                        onChange={(event) =>
                            event.persist() ||
                            setVals((vals) => ({
                                ...vals,
                                rendered: event.target.value,
                            }))
                        }
                    ></Slider>
                    <h4>Slider with a bound child (dropdown)</h4>
                    <Slider
                        id="withChild-slider"
                        theme={theme}
                        variant={secondary}
                        childrenOffset={45}
                        displayValue={
                            vals.withChild.value + vals.withChild.unit
                        }
                        value={vals.withChild.value}
                        onChange={(event) =>
                            event.persist() ||
                            setVals((vals) => ({
                                ...vals,
                                withChild: {
                                    ...vals.withChild,
                                    value: event.target.value,
                                },
                            }))
                        }
                    >
                        <Dropdown
                            theme={theme}
                            onChange={(newVal) =>
                                setVals((vals) => ({
                                    ...vals,
                                    withChild: {
                                        ...vals.withChild,
                                        unit: newVal,
                                    },
                                }))
                            }
                            value={vals.withChild.unit}
                            options={[
                                { name: 'cm', value: 'cm' },
                                { name: 'm', value: 'm' },
                                { name: 'km', value: 'km' },
                            ]}
                            title="Units"
                        />
                    </Slider>
                    <div style={heightSpacer}></div>
                </Card>
            </div>
        </>
    )
}
