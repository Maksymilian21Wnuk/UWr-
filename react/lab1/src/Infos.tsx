import React from "react";
import "./styles.css";
import about from "./about_me";

interface InfoProps {
  type: string;
  msg: string;
}

interface AboutProps {
  msg: string;
}

const About: React.FC<AboutProps> = ({ msg }) => {
  return (
    <div className="info">
      <h3>About me</h3>
      <div className="about">{msg}</div>
    </div>
  );
};

const Info: React.FC<InfoProps> = ({ type, msg }) => {
  return (
    <div className="info">
      <p>{type + "  " + msg}</p>
    </div>
  );
};

export const Infos = () => {
  return (
    <main>
      <Info msg="502-312-321" type="&#128222;" />
      <Info msg="my_mail@gmail.com" type="&#x1F4E7;" />
      <Info msg="my_site.com" type="&#x1F310;" />
      <About msg={about} />
    </main>
  );
};
