import React from "react"
import Logo from "../images/react-icon.png"
import "./style/Header.css"

function Header() {
    return (
        <div className="header">
            <div>
                <img src={Logo}/>
                <h1>ReactFacts</h1>
            </div>
            <h2>React Course - Project 1</h2>
        </div>
    )
}

export default Header