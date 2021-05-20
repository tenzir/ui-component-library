import React from 'react'
import { Prism as SyntaxHighlighter } from 'react-syntax-highlighter'
import { okaidia } from 'react-syntax-highlighter/dist/esm/styles/prism'
import { useDarkMode } from 'storybook-dark-mode'
import { make as Alert } from '../src/Alert.bs.js'
import { FiActivity as Activity } from 'react-icons/fi'
import { make as Card } from '../src/Card.bs.js'
import { small, medium, large, light, dark } from '../src/UiTypes.bs'
import {
    primary,
    secondary,
    success,
    warning,
    danger,
} from '../src/AlertStyles.bs'

export default {
    title: 'Alert',
}

const margin = {
    margin: '1rem',
}

export const Alerts = () => {
    const theme = useDarkMode() ? dark : light
    return (
        <div style={margin}>
            <Card depth={0} theme={theme}>
                <h1>Alerts</h1>
                <h3>Interface</h3>
                <SyntaxHighlighter
                    language="reason"
                    style={okaidia}
                    showLineNumbers
                >
                    {`type Alert: (
  ~message: option(string),
  ~children: option(React.Element), /* Note that both message and children can be passed in at once */
  ~variant: AlertStyles.variant,
  ~size: UiTypes.size,
  ~className: option(string),
  ~theme: option(UiTypes.theme)
) => React.element;
`}
                </SyntaxHighlighter>

                <h3>Preview</h3>
                <Alert message="This is an info alert" variant={primary} />
                <Alert
                    message="This is a toned down info alert"
                    variant={secondary}
                />
                <Alert message="This is a success alert" variant={success} />
                <Alert message="This is a warning alert" variant={warning} />
                <Alert message="This is a danger alert" variant={danger} />

                <h3>Sizes</h3>
                <Alert size={small} message="Small" variant={primary} />
                <Alert size={medium} message="Medium" variant={primary} />
                <Alert size={large} message="Large" variant={primary} />
            </Card>
        </div>
    )
}
