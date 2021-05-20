import React from 'react'
import { make as Button, Group } from '../src/Button.bs.js'
import { Prism as SyntaxHighlighter } from 'react-syntax-highlighter'
import { okaidia } from 'react-syntax-highlighter/dist/esm/styles/prism'
import { useDarkMode } from 'storybook-dark-mode'
import { FiActivity as Activity } from 'react-icons/fi'
import { make as Card } from '../src/Card.bs.js'
import { small, medium, large, light, dark } from '../src/UiTypes.bs'
import {
    primary,
    secondary,
    success,
    warning,
    danger,
} from '../src/ButtonStyles.bs'

const ButtonGroup = Group.make
export default {
    title: 'Button',
}

const margin = {
    margin: '1rem',
}

const buttons = [
    { variant: primary, text: 'Primary' },
    { variant: secondary, text: 'Secondary' },
    { variant: success, text: 'Success' },
    { variant: warning, text: 'Warning' },
    { variant: danger, text: 'Danger' },
]

export const Buttons = () => {
    const theme = useDarkMode() ? dark : light
    return (
        <>
            <div style={margin}>
                <Card theme={theme}>
                    <h1>Buttons</h1>
                    <h3>Interface</h3>
                    <SyntaxHighlighter
                        language="reason"
                        style={okaidia}
                        showLineNumbers
                    >
                        {`type Button: (
  ~disabled:boolean,
  ~type_: string,
  ~variant:ButtonStyles.Primary
  ~theme: option(UiTypes.theme)),
  ~size=UiTypes.size,
  ~icon=option(React.Element),
  ~onClick=option(React.SyntheticEvent.t->unit),
  ~children=option(React.Element)
)=> React.element;`}
                    </SyntaxHighlighter>

                    <h3>Previews</h3>
                    <h4>Normal Buttons</h4>
                    {buttons.map(({ variant, text }) => (
                        <span key={variant + text} style={margin}>
                            <Button theme={theme} variant={variant}>
                                {text}
                            </Button>
                        </span>
                    ))}

                    <h4>Small / Medium / Large</h4>
                    <div>
                        {buttons.map(({ variant, text }) => (
                            <span key={variant + text + 'small'} style={margin}>
                                <Button
                                    theme={theme}
                                    variant={variant}
                                    size={small}
                                >
                                    {text}
                                </Button>
                            </span>
                        ))}
                    </div>
                    <div>
                        {buttons.map(({ variant, text }) => (
                            <span
                                key={variant + text + 'medium'}
                                style={margin}
                            >
                                <Button
                                    theme={theme}
                                    variant={variant}
                                    size={medium}
                                >
                                    {text}
                                </Button>
                            </span>
                        ))}
                    </div>
                    <div>
                        {buttons.map(({ variant, text }) => (
                            <span key={variant + text + 'large'} style={margin}>
                                <Button
                                    theme={theme}
                                    variant={variant}
                                    size={large}
                                >
                                    {text}
                                </Button>
                            </span>
                        ))}
                    </div>

                    <h4>Disabled</h4>
                    {buttons.map(({ variant, text }) => (
                        <span key={variant + text} style={margin}>
                            <Button disabled theme={theme} variant={variant}>
                                {text}
                            </Button>
                        </span>
                    ))}

                    <h4>With Icons</h4>
                    {buttons.map(({ variant, text }) => (
                        <span key={variant + text} style={margin}>
                            <Button
                                icon={<Activity />}
                                theme={theme}
                                variant={variant}
                            >
                                {text}
                            </Button>
                        </span>
                    ))}

                    <h4>Grouped</h4>
                    {buttons.map(({ variant, text }) => (
                        <span key={variant + text} style={margin}>
                            <ButtonGroup>
                                <Button theme={theme} variant={variant}>
                                    {text}
                                </Button>
                                <Button theme={theme} variant={variant}>
                                    {text}
                                </Button>
                                <Button
                                    icon={<Activity />}
                                    theme={theme}
                                    variant={variant}
                                >
                                    {text}
                                </Button>
                            </ButtonGroup>
                        </span>
                    ))}

                    <h4>Grouped with Mixed Variants</h4>
                    {buttons.map(({ variant, text }) => (
                        <span key={variant + text} style={margin}>
                            <ButtonGroup>
                                <Button theme={theme} variant={secondary}>
                                    {text}
                                </Button>
                                <Button
                                    icon={<Activity />}
                                    theme={theme}
                                    variant={variant}
                                >
                                    {text}
                                </Button>
                            </ButtonGroup>
                        </span>
                    ))}
                </Card>
            </div>
        </>
    )
}
