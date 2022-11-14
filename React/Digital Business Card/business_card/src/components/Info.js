import React from "react"
import Image from "../images/profile-picture.jpg"
import "./style/Info.css"

function Info() {
    

    return(
    <div className="info">
        <img className="info--image" src={Image}/>
        <p className="info--name">Daniel Cogiel</p>
        <p className="info--description">Silesian University of Technology student</p>
        <a target="blank" className="info--link" href="https://www.linkedin.com/in/daniel-cogiel-4a619723b/">
            https://www.linkedin.com/in/daniel-cogiel-4a619723b/
        </a>
        <div className="info--button--container">
            <a href="mailto:dcogiel.work@gmail.com"><button className="info--button--email"><span class="material-symbols-outlined">mail</span>  Email</button></a>
            <a target="blank" href="https://www.linkedin.com/in/daniel-cogiel-4a619723b/overlay/contact-info/">
                <button className="info--button--linkedin"><i className="fa fa-linkedin-square"></i>  LinkedIn</button>
            </a>
        </div>
    </div>
    )
}

export default Info