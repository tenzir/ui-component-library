import React from 'react'
import { make as Input } from '../src/Input.bs.js'
import { Prism as SyntaxHighlighter } from 'react-syntax-highlighter'
import { okaidia } from 'react-syntax-highlighter/dist/esm/styles/prism'
import { useDarkMode } from 'storybook-dark-mode'
import { make as Card } from '../src/Card.bs.js'
import { make as Notifications } from '../src/Notifications.bs.js'
import {
    labeled,
    light,
    dark,
    normal,
    mono,
    valid,
    invalid,
} from '../src/UiTypes.bs'
import { tiny, huge } from '../src/CardStyles.bs'

export default {
    title: 'Notifications',
}

const margin = {
    margin: '1rem',
}

export const nofitication = () => {
    const theme = useDarkMode() ? dark : light

    const [notifications, setNotifications] = React.useState([
        { id: 0, title: 'I just have a title' },
        { id: 1, title: 'I also have a body', body: 'Here is the body' },
        {
            id: 2,
            title: 'I have an action',
            action: ['Action Title', () => alert('Hello')],
        },
        {
            id: 3,
            title: 'I go away automagically',
            body: 'Here is some text to go with my notification',
            action: ['Action Title', () => alert('Hello')],
        },
    ])

    return (
        <div style={margin}>
            <Card theme={theme}>
                <h1>Notification</h1>

                <h3>Interface</h3>
                <p>
                    There are two types to care about when using these. The
                    first one is the Notification itself, the second one is the
                    one that handles the display logic. The design is made in
                    such a way that there is a pure way to handle the showing /
                    hiding of notifications by updating the list. It is expected
                    of an implementer to implement the logic for this. We use a
                    centralized store management solution and feed the list into
                    it from there.
                </p>
                <SyntaxHighlighter
                    language="reason"
                    style={okaidia}
                    showLineNumbers
                >
                    {`type Notification: {
  id: string,
  title: string,
  body: option(string),
  action: option(unit => unit),
  timeout: option(int),
};

type Notifications
  ~notifications: array(Notification),
  ~handleDismissal: option(id => unit),
) => React.element;
`}
                </SyntaxHighlighter>

                <h3>Preview</h3>
                <Notifications notifications={notifications} theme={theme} />
            </Card>
        </div>
    )
}
