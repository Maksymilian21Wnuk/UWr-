import React from "react";
import "./styles.css";

interface AppProps {
  skill: string;
}

const Skills: React.FC<AppProps> = ({ skill }) => {
  return (
    <div className="skills">
      <p>{skill}</p>
    </div>
  );
};
export default Skills;
