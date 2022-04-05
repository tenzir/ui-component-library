import React from 'react'
import { Prism as SyntaxHighlighter } from 'react-syntax-highlighter'
import { make as Button, Group } from '../src/Button.bs.js'
import { okaidia } from 'react-syntax-highlighter/dist/esm/styles/prism'
import { useDarkMode } from 'storybook-dark-mode'
import { make as Card, Tabbed } from '../src/Card.bs.js'
import { make as Tabs, Helpers } from '../src/Tabs.bs.js'
import { light, dark } from '../src/UiTypes.bs'
import { tiny, large, huge } from '../src/CardStyles.bs'

export default {
    title: 'Tabs',
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
    width: '20%',
    margin: '1rem',
    display: 'inline-block',
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

export const tabs = () => {
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
                    {`type tab = {
  id: string,
  title: string,
};

type Tabs: (
   ~activeTabId: string;
   ~depth: option(int);
   ~addButtonText: option(string); // Defaults to "New"
   ~onAdd: option(t -> unit);
   ~onClose: option(string -> unit);
   ~onDuplicate: option(string -> unit);
   ~onMove: option(( int, int ) -> unit);
   ~onOpen: option(string -> unit);
   ~onRename: option(t -> unit);
   ~standalone: option(bool);
   ~tabs: array(t);
   ~theme: UiTypes.theme;
) => React.element;`}
                </SyntaxHighlighter>

                <h3>Preview</h3>
                <p>
                    Tabs support a number of callbacks:
                    <ul>
                        <li>Add a tab (onAdd)</li>
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
                <h3>All Functionality Enabled</h3>
                <div style={smallCardContainerWide}>
                    <Tabs
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
                        depth={2}
                        theme={theme}
                    >
                        <h2>Tabs</h2>
                        <p>
                            Active Tab:{' '}
                            {tabs.find((x) => x.id === activeTabId).title}
                        </p>
                    </Tabs>
                </div>
                <h3>All Functionality Enabled - hiding add text</h3>
                <div style={smallCardContainerWide}>
                    <Tabs
                        addButtonText={null}
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
                        depth={2}
                        theme={theme}
                    >
                        <h2>Tabs</h2>
                        <p>
                            Active Tab:{' '}
                            {tabs.find((x) => x.id === activeTabId).title}
                        </p>
                    </Tabs>
                </div>
                <h3>No Duplication</h3>
                <div style={smallCardContainerWide}>
                    <Tabs
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
                        tabs={tabs}
                        activeTabId={activeTabId}
                        depth={2}
                        theme={theme}
                    >
                        <h2>Tabs</h2>
                        <p>
                            Active Tab:{' '}
                            {tabs.find((x) => x.id === activeTabId).title}
                        </p>
                    </Tabs>
                </div>
                <h3>No Duplication or Moving</h3>
                <div style={smallCardContainerWide}>
                    <Tabs
                        onOpen={setActiveTabId}
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
                        tabs={tabs}
                        activeTabId={activeTabId}
                        depth={2}
                        theme={theme}
                    >
                        <h2>Tabs</h2>
                        <p>
                            Active Tab:{' '}
                            {tabs.find((x) => x.id === activeTabId).title}
                        </p>
                    </Tabs>
                </div>
                <h3>No Duplication or Moving or Renaming</h3>
                <div style={smallCardContainerWide}>
                    <Tabs
                        onOpen={setActiveTabId}
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
                        tabs={tabs}
                        activeTabId={activeTabId}
                        depth={2}
                        theme={theme}
                    >
                        <h2>Tabs</h2>
                        <p>
                            Active Tab:{' '}
                            {tabs.find((x) => x.id === activeTabId).title}
                        </p>
                    </Tabs>
                </div>
                <h3>Only Opening</h3>
                <div style={smallCardContainerWide}>
                    <Tabs
                        onOpen={setActiveTabId}
                        tabs={tabs}
                        activeTabId={activeTabId}
                        depth={2}
                        theme={theme}
                    >
                        <h2>Tabs</h2>
                        <p>
                            Active Tab:{' '}
                            {tabs.find((x) => x.id === activeTabId).title}
                        </p>
                    </Tabs>
                </div>
            </Card>
        </div>
    )
}

export const TabHelpers = () => {
    const theme = useDarkMode() ? dark : light
    return (
        <Card theme={theme}>
            <h1>Helper Functions </h1>
            <p>
                These helper functions should abstract away most of the logic of
                updating the underlying array of tabs. They are quite self
                explanatory given the name and type signature.
            </p>
            <SyntaxHighlighter
                language="reason"
                style={okaidia}
                showLineNumbers
            >
                {`type create: string -> t
type createMany: array(string) -> array(t)
type add: (array(t), t) -> array(t)
type update: (array(t), t) -> array(t)
type removeById: (array(t), string) -> array(t)
type removeByIndex: (array(t), int) -> array(t)
type duplicateById: (array(t), string) -> array(t)
type duplicateByIdx: (array(t), int) -> array(t)
type move : (array(t), int, int) -> array(t) /* from / to */`}
            </SyntaxHighlighter>
        </Card>
    )
}
