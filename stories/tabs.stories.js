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
            title: 'Some uncomfortably long tab title that will never fit',
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
   ~onClose: option(string -> unit) option;
   ~onDuplicate: option(string -> unit) option;
   ~onMove: option(( int, int ) -> unit) option;
   ~onOpen: option(string -> unit) option;
   ~onUpdate: option(t -> unit) option;
   ~standalone: option(bool);
   ~tabs: array(t);
   ~theme: UiTypes.theme;
) => React.element;`}
                </SyntaxHighlighter>

                <h3>Preview</h3>
                <h4>A Tabbed card with all features enabled:</h4>
                <p>
                    Features can be disabled by omitting the functionality. I.e
                    if there is no function to update the tab, the text won't be
                    editable.
                </p>
                <div style={smallCardContainerWide}>
                    <Tabs
                        onOpen={setActiveTabId}
                        onMove={([from, to]) => {
                            setTabs(Helpers.move(tabs, from, to))
                        }}
                        onUpdate={(x) => {
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
            </Card>
        </div>
    )
}
