import React from 'react'
import { Prism as SyntaxHighlighter } from 'react-syntax-highlighter'
import { okaidia } from 'react-syntax-highlighter/dist/esm/styles/prism'
import { useDarkMode } from 'storybook-dark-mode'
import { make as Card } from '../src/Card.bs.js'
import { light, dark } from '../src/UiTypes.bs'

export default {
    title: 'Typography',
}

const margin = {
    margin: '1rem',
}

export const typograph = () => {
    const theme = useDarkMode() ? dark : light
    return (
        <>
            <div style={margin}>
                <Card theme={theme}>
                    <h1>Typography</h1>
                    <h1>This is an h1 title</h1>
                    <h2>This is an h2 title</h2>
                    <h3>This is an h3 title</h3>
                    <h4>This is an h4 title</h4>
                    <h5>This is an h5 title</h5>
                    <h6>This is an h6 title</h6>
                    <p>Here is the paragraph text</p>
                    <ul>
                        <li>I'm in an unordered list</li>
                        <li>I'm in an unordered list</li>
                    </ul>
                    <ol>
                        <li>I'm in an ordered list</li>
                        <li>I'm in an ordered list</li>
                    </ol>
                </Card>
            </div>
        </>
    )
}
