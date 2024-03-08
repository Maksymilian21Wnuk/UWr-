import React from "react";
import "./styles.css";

interface AppProps {
  skill: string;
}

const Skill: React.FC<AppProps> = ({ skill }) => {
  return (
    <div className="skills">
      <p>{skill}</p>
    </div>
  );
};

export const Skills = () => {
  return (
    <main>
      <h3>My Skills</h3>
      <div className="skills_container">
        <Skill skill="HTML" />
        <Skill skill="CSS" />
        <Skill skill="JavaScript" />
        <Skill skill="React" />
        <Skill skill="TypeScript" />
        <Skill skill="Node.js" />
        <Skill skill="MongoDB" />
      </div>
    </main>
  );
};
