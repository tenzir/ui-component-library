import React from 'react'
import { Prism as SyntaxHighlighter } from 'react-syntax-highlighter'
import { okaidia } from 'react-syntax-highlighter/dist/esm/styles/prism'
import { useDarkMode } from 'storybook-dark-mode'
import { make as Dropdown } from '../src/Dropdown.bs.js'
import { make as ActionDropdown } from '../src/ActionDropdown.bs.js'
import { FiActivity as Activity } from 'react-icons/fi'
import { make as Card } from '../src/Card.bs.js'
import { light, dark } from '../src/UiTypes.bs'
import {
    primary,
    secondary,
    success,
    warning,
    danger,
} from '../src/ButtonStyles.bs'

export default {
    title: 'Dropdown',
}

const dropdownContainer = {
    display: 'inline-block',
    width: '40%',
    marginRight: '100px',
    paddingBottom: '300px',
}
const margin = {
    margin: '1rem',
}

export const Dropdowns = () => {
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
                    {`type t('a) = {
  name: string,
  value: 'a,
};

type Dropdown: (
  ~theme: option(UiTypes.theme)
  ~options: array(t('a)),
  ~disabled: option(bool), /* defaults to false */
  ~enableSearch: option(bool), /* defaults to false */
  ~value: 'a,
  ~depth: option(int), /* defaults to 1 */
  ~minWidth: option(int), /* in px, defaults to 150, width for the button */
  ~maxHeight: option(int), /* in px, defaults to 200, height for the dropdown */
  ~onChange: 'a => unit,
  ~title: option(string),
  ~className: option(string), /* Defaults to empty string */
) => React.element;
`}
                </SyntaxHighlighter>

                <h3>Preview</h3>
                <div style={dropdownContainer}>
                    <p>A regular dropdown</p>
                    <Dropdown
                        theme={theme}
                        onChange={setValue}
                        value={value}
                        options={[
                            { name: 'Lorem', value: 0 },
                            { name: 'Ipsum', value: 1 },
                            { name: 'Dolor', value: 2 },
                            { name: 'Sit', value: 3 },
                            { name: 'Amet', value: 4 },
                            { name: 'Consectetur', value: 5 },
                        ]}
                        title="Sample"
                    />
                </div>
                <div style={dropdownContainer}>
                    <p>A regular dropdown with a built in filter</p>
                    <Dropdown
                        theme={theme}
                        onChange={setValue}
                        enableSearch
                        value={value}
                        options={[
                            { name: 'Lorem', value: 0 },
                            { name: 'Ipsum', value: 1 },
                            { name: 'Dolor', value: 2 },
                            { name: 'Sit', value: 3 },
                            { name: 'Amet', value: 4 },
                            { name: 'Consectetur', value: 5 },
                        ]}
                        title="Sample"
                    />
                </div>
                <div style={dropdownContainer}>
                    <p>A regular dropdown without anything</p>
                    <Dropdown
                        theme={theme}
                        onChange={setValue}
                        variant={primary}
                        value={value}
                        options={[
                            { name: 'Lorem', value: 0 },
                            { name: 'Ipsum', value: 1 },
                            { name: 'Dolor', value: 2 },
                            { name: 'Sit', value: 3 },
                            { name: 'Amet', value: 4 },
                            { name: 'Consectetur', value: 5 },
                        ]}
                        title="Sample"
                    />
                </div>
                <div style={dropdownContainer}>
                    <p>A regular dropdown without anything</p>
                    <Dropdown
                        theme={theme}
                        onChange={setValue}
                        variant={danger}
                        value={value}
                        options={[
                            { name: 'Lorem', value: 0 },
                            { name: 'Ipsum', value: 1 },
                            { name: 'Dolor', value: 2 },
                            { name: 'Sit', value: 3 },
                            { name: 'Amet', value: 4 },
                            { name: 'Consectetur', value: 5 },
                        ]}
                        title="Sample"
                    />
                </div>
            </Card>
        </div>
    )
}

export const ActionDropdowns = () => {
    const theme = useDarkMode() ? dark : light
    const [value, setValue] = React.useState(0)
    return (
        <div style={margin}>
            <Card depth={0} theme={theme}>
                <h1>Action Dropdowns</h1>
                <h3>Interface</h3>
                <SyntaxHighlighter
                    language="reason"
                    style={okaidia}
                    showLineNumbers
                >
                    {`type t('a) = {
  name: string,
  value: 'a,
  action: unit -> unit
};

type Dropdown: (
  ~theme: option(UiTypes.theme)
  ~options: array(t('a)),
  ~disabled: option(bool), /* defaults to false */
  ~enableSearch: option(bool), /* defaults to false */
  ~value: 'a,
  ~depth: option(int), /* defaults to 1 */
  ~minWidth: option(int), /* in px, defaults to 150, width for the button */
  ~maxHeight: option(int), /* in px, defaults to 200, height for the dropdown */
  ~callActionOnChange=false,
  ~onChange: 'a => unit,
  ~title: option(string),
  ~className: option(string), /* Defaults to empty string */
) => React.element;
`}
                </SyntaxHighlighter>

                <h3>Preview</h3>
                <div style={dropdownContainer}>
                    <p>A dropdown that calls actions</p>
                    <ActionDropdown
                        theme={theme}
                        onChange={setValue}
                        value={value}
                        options={[
                            {
                                name: 'Lorem',
                                value: 0,
                                action: () => alert('Hello'),
                            },
                            {
                                name: 'Ipsum',
                                value: 1,
                                action: () => alert('Hello from no. 2'),
                            },
                        ]}
                        title="Sample"
                    />
                </div>
            </Card>
        </div>
    )
}
