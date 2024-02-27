import React from "react";
import "./styles.css";

interface AppProps {
  type: string;
  msg: string;
}
const Info: React.FC<AppProps> = ({ type, msg }) => {
  if (type == "about") {
    return (
      <div className="info">
        <h3>About me</h3>
        <div className="about">{msg}</div>
      </div>
    );
  } else {
    return (
      <div className="info">
        <p>{type + "  " + msg}</p>
      </div>
    );
  }
};
export default Info;
