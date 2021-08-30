import React from 'react'
import { Prism as SyntaxHighlighter } from 'react-syntax-highlighter'
import { make as Button, Group } from '../src/Button.bs.js'
import { okaidia } from 'react-syntax-highlighter/dist/esm/styles/prism'
import { useDarkMode } from 'storybook-dark-mode'
import { make as Card, Tabbed } from '../src/Card.bs.js'
import { Helpers } from '../src/Tabs.bs.js'
import { light, dark } from '../src/UiTypes.bs'
import { tiny, large, huge } from '../src/CardStyles.bs'

const TabbedCard = Tabbed.make
export default {
    title: 'Card',
}

const cardContainer = {
    width: '20%',
    height: '500px',
    margin: '1rem',
    display: 'inline-block',
}

const smallCardContainer = {
    ...cardContainer,
    height: '200px',
}

const smallCardContainerWide = {
    ...smallCardContainer,
    width: '80%',
}

const nestedCardContainer = {
    ...cardContainer,
    width: '40%',
    height: 'unset',
}

const headerStyles = {
    padding: '0 1.5rem',
}

const footerStyles = {
    width: '100%',
    padding: '0 0.5rem',
    display: 'flex',
    justifyContent: 'flex-end',
}

const margin = {
    margin: '1rem',
}

export const card = () => {
    const theme = useDarkMode() ? dark : light
    return (
        <div style={margin}>
            <Card theme={theme}>
                <h1>Cards</h1>
                <h3>Interface</h3>
                <SyntaxHighlighter
                    language="reason"
                    style={okaidia}
                    showLineNumbers
                >
                    {`type Card: (
  ~onMouseOut: option(ReactEvent.Mouse.t -> unit),
  ~onMouseOver: option(ReactEvent.Mouse.t -> unit),
  ~spacing: option(CardStyles.spacing),
  ~theme: option(UiTypes.theme),
  ~depth: option(int),
  ~header: option(React.Element),
  ~footer: option(React.Element),
  ~children: option(React.Element),
  ~className: option(string),
) => React.element;`}
                </SyntaxHighlighter>

                <h3>Preview</h3>
                <h4>Padding</h4>
                <div style={smallCardContainer}>
                    <Card spacing={tiny} depth={2} theme={theme}>
                        <h2>Tiny Padding</h2>
                    </Card>
                </div>
                <div style={smallCardContainer}>
                    <Card depth={2} theme={theme}>
                        <h2>Normal Padding</h2>
                    </Card>
                </div>
                <div style={smallCardContainer}>
                    <Card spacing={large} depth={2} theme={theme}>
                        <h2>Large Padding</h2>
                    </Card>
                </div>
                <div style={smallCardContainer}>
                    <Card spacing={huge} depth={2} theme={theme}>
                        <h2>Huge Padding</h2>
                    </Card>
                </div>

                <h4>Nesting</h4>
                <p>
                    Using the 'Depth' Parameter, one can stack multiple cards.
                    The stacking here actuall starts with the background, which
                    is one of our cards.
                </p>
                <div style={nestedCardContainer}>
                    <Card spacing={tiny} depth={2} theme={theme}>
                        <h2>No. 1</h2>
                        <Card spacing={tiny} depth={3} theme={theme}>
                            <h2>No. 2</h2>
                            <Card spacing={tiny} depth={4} theme={theme}>
                                <h2>Cards all the way down</h2>
                            </Card>
                        </Card>
                    </Card>
                </div>

                <h4>Header / Footer</h4>
                <p>
                    One can pass in a header and footer component. To be as
                    flexible as possible here, we do not implement any spacing
                    options here. The component passed into the header should
                    place itself according to the space available
                </p>
                <div style={nestedCardContainer}>
                    <Card
                        header={
                            <div style={headerStyles}>
                                <h3>Some Header</h3>
                            </div>
                        }
                        footer={
                            <div style={headerStyles}>
                                <h3>Some Footer</h3>
                            </div>
                        }
                        spacing={tiny}
                        depth={2}
                        theme={theme}
                    >
                        <h2>No. 1</h2>
                        <p>Some text inside here still</p>
                    </Card>
                </div>
                <div style={nestedCardContainer}>
                    <Card
                        header={
                            <div style={headerStyles}>
                                <h3>Login</h3>
                            </div>
                        }
                        footer={
                            <div style={footerStyles}>
                                <Button>Login</Button>
                            </div>
                        }
                        spacing={tiny}
                        depth={2}
                        theme={theme}
                    >
                        <p>Some forms could go here...</p>
                    </Card>
                </div>
            </Card>
        </div>
    )
}

export const cardWithTabs = () => {
    const theme = useDarkMode() ? dark : light
    const [tabs, setTabs] = React.useState([
        {
            id: 'one',
            title: 'foo',
        },
        {
            id: 'two',
            title: 'bar',
        },
        {
            id: 'three',
            title: 'baz',
        },
    ])
    const [activeTabId, setActiveTabId] = React.useState('one')
    return (
        <div style={margin}>
            <Card theme={theme}>
                <h1>Tabbed Card</h1>
                <h3>Interface</h3>
                <SyntaxHighlighter
                    language="reason"
                    style={okaidia}
                    showLineNumbers
                >
                    {`type Card: (
   ~onMouseOver: option(ReactEvent.Mouse.t => unit),
   ~onMouseOut: option(ReactEvent.Mouse.t => unit),
   ~spacing: option(CardStyles.spacing),
   ~theme: option(UiTypes.theme),
   ~depth: option(int),
   ~className: option(string),
   ~footer: option(React.element),
   ~children: option(React.element),
   /* Tab specific */
   ~activeTabId: string, /* tabId */
   ~tabs: array(Tabs.t),
   ~onMove: option(((int, int)) => unit), /* (fromIdx, toIdx) */
   ~onOpen: option(string => 'a), /* tabId */
   ~onClose: option(string => 'a), /* tabId */
   ~onDuplicate: option(string => 'a), /* tabId */
   ~onRename: option(Tabs.t => 'a),
) => React.element;`}
                </SyntaxHighlighter>

                <h3>Preview</h3>
                <p>
                    Tabs support a number of callbacks:
                    <ul>
                        <li>Open a tab (onMove)</li>
                        <li>Close a tab (onClose)</li>
                        <li>Duplicate a tab (onDuplicate)</li>
                        <li>Rename a tab (onRename)</li>
                        <li>Move a tab (via drag 'n drop) (onMove)</li>
                    </ul>
                    Features can be disabled by omitting the callback. I.e if
                    there is no function to rename the tab, the text won't be
                    editable.
                </p>
                <div style={smallCardContainerWide}>
                    <TabbedCard
                        onAdd={(newTab) => {
                            setTabs((tabs) => Helpers.add(tabs, newTab))
                            setActiveTabId(newTab.id)
                        }}
                        onOpen={setActiveTabId}
                        onMove={([from, to]) => {
                            setTabs(Helpers.move(tabs, from, to))
                        }}
                        onRename={(x) => {
                            setTabs((tabs) => Helpers.update(tabs, x))
                        }}
                        onClose={(x) => {
                            const tabIdx = tabs.findIndex((y) => y.id === x)
                            console.log(tabIdx, x)
                            if (tabs[tabIdx + 1]) {
                                setActiveTabId(tabs[tabIdx + 1].id)
                            } else if (tabs[tabIdx - 1]) {
                                setActiveTabId(tabs[tabIdx - 1].id)
                            } else {
                                setActiveTabId('')
                            }
                            setTabs((tabs) => Helpers.removeById(tabs, x))
                        }}
                        onDuplicate={(x) => {
                            const [newTabs, newId] = Helpers.duplicateById(
                                tabs,
                                x
                            )
                            setActiveTabId(newId)
                            setTabs(newTabs)
                        }}
                        tabs={tabs}
                        activeTabId={activeTabId}
                        spacing={tiny}
                        depth={2}
                        theme={theme}
                    >
                        <h2>Tabs</h2>
                        <p>
                            Active Tab:{' '}
                            {tabs.find((x) => x.id === activeTabId).title}
                        </p>
                    </TabbedCard>
                </div>
                <h4>A Tabbed card with almost no features enabled</h4>
                <div style={smallCardContainerWide}>
                    <TabbedCard
                        onOpen={setActiveTabId}
                        tabs={tabs}
                        activeTabId={activeTabId}
                        spacing={tiny}
                        depth={2}
                        theme={theme}
                    >
                        <h2>Tabs</h2>
                        <p>
                            Active Tab:{' '}
                            {tabs.find((x) => x.id === activeTabId).title}
                        </p>
                    </TabbedCard>
                </div>
            </Card>
        </div>
    )
}
