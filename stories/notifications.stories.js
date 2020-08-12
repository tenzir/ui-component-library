import React from 'react'
import { Group, make as Button } from '../src/Button.bs.js'
import { secondary } from '../src/ButtonStyles.bs.js'
import { make as Input } from '../src/Input.bs.js'
import { Prism as SyntaxHighlighter } from 'react-syntax-highlighter'
import { okaidia } from 'react-syntax-highlighter/dist/esm/styles/prism'
import { useDarkMode } from 'storybook-dark-mode'
import { make as Card } from '../src/Card.bs.js'
import { create as createNotification } from '../src/Notification.bs.js'
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

const ButtonGroup = Group.make

export const notifications = () => {
    const theme = useDarkMode() ? dark : light

    const [notifications, setNotifications] = React.useState([
        { id: 0, title: 'Here is the Preview' },
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
            timeout: 3000,
            action: ['Action Title', () => alert('Hello')],
        },
        {
            id: 4,
            title: 'I go away automagically',
            body: 'But hang around a little longer than my mate',
            timeout: 8000,
        },
    ])

    const addNotification = (notification) => (e) => {
        setNotifications((arr) => [...arr, notification])
    }

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
                    it from there. Note that the timeout is defined as a tuple
                    of string / unit -> unit. The string holds the line that
                    get's put into the button.
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
  action: option((string, unit => unit)),
  timeout: option(int),
};

type Notifications
  ~notifications: array(Notification),
  ~handleDismissal: option(id => unit),
  ~defaultAnimationTime: int, /* In ms,  Defaults to 400 */
  ~maxAmount: int, /* Max notifications to show at one point in time. Defaults to 5 */
) => React.element;
`}
                </SyntaxHighlighter>
                <h3>Helper</h3>
                <p>Try it:</p>
                <ButtonGroup>
                    <Button
                        variant={secondary}
                        theme={theme}
                        onClick={addNotification(
                            createNotification(
                                undefined,
                                undefined,
                                undefined,
                                undefined,
                                'Just a title'
                            )
                        )}
                    >
                        Plain
                    </Button>

                    <Button
                        variant={secondary}
                        theme={theme}
                        onClick={addNotification(
                            createNotification(
                                undefined,
                                'Also a body',
                                undefined,
                                undefined,
                                'Title'
                            )
                        )}
                    >
                        Body
                    </Button>

                    <Button
                        variant={secondary}
                        theme={theme}
                        onClick={addNotification(
                            createNotification(
                                undefined,
                                'Body',
                                ['Also an action', () => alert('Hello')],
                                undefined,
                                'Title'
                            )
                        )}
                    >
                        Action
                    </Button>

                    <Button
                        variant={secondary}
                        theme={theme}
                        onClick={addNotification(
                            createNotification(
                                undefined,
                                'Body',
                                ['Action', () => alert('Hello')],
                                2000,
                                'Title'
                            )
                        )}
                    >
                        Timeout
                    </Button>
                </ButtonGroup>

                <h3>Helper</h3>
                <p>
                    To aid with the creation of these, rather than declaring
                    them with a record type, we expose a convienience function
                    with sane defaults for all optional values and automatic id
                    creation with the help of 'uuid.v4()'. With the help of
                    optional arguments, we can make the creation much less
                    verbose.
                </p>

                <SyntaxHighlighter
                    language="reason"
                    style={okaidia}
                    showLineNumbers
                >
                    {`type Notification.create: (
  ~id: string, /* Defaults to uuid.v4() */
  ~body: option(string), /* Defaults to None */
  ~action: option(string), /* Defaults to None */
  ~timeout: option((string, unit => unit)), /* Defaults to None */
  title: string, /* No default, the only fixed parameter */
);

let a = Notification.create("Just a title");
let b = Notification.create(~body="Also a body", "Just a title");

`}
                </SyntaxHighlighter>

                <Notifications
                    handleDismissal={(notificationId) =>
                        setNotifications((arr) =>
                            arr.filter(({ id }) => id !== notificationId)
                        )
                    }
                    notifications={notifications}
                    theme={theme}
                />
            </Card>
        </div>
    )
}
