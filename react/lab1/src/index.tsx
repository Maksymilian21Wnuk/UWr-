import ReactDOM from "react-dom";
import { StrictMode } from "react";

import App from "./App";
import Image from "./Image";
import Info from "./Info";
import about from "./about_me";
import Skills from "./Skills";

const rootElement = document.getElementById("root");
const root = ReactDOM.createRoot(rootElement);

root.render(
  <StrictMode>
    <Image />
    <App name="Tomasz Kowalski" company="TomaszPOL" job="Frontend Developer" />
    <Info msg="502-312-321" type="&#128222;" />
    <Info msg="my_mail@gmail.com" type="&#x1F4E7;" />
    <Info msg="my_site.com" type="&#x1F310;" />
    <Info msg={about} type="about" />
    <h3>My Skills</h3>
    <div className="skills_container">
      <Skills skill="HTML" />
      <Skills skill="CSS" />
      <Skills skill="JavaScript" />
      <Skills skill="React" />
      <Skills skill="TypeScript" />
      <Skills skill="Node.js" />
      <Skills skill="MongoDB" />
    </div>
  </StrictMode>
);
