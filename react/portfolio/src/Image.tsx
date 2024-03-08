import React from "react";
import "./styles.css";
import profile_pic from "./profile_pic.jpg";

const Image: React.FC = () => {
  return (
    <div className="image">
      <img src={profile_pic} alt="Avatar" />
    </div>
  );
};
export default Image;
