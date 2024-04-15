import React, { useState } from "react";
import { Button, TextField, Stack, Alert } from "@mui/material";
import { Foods } from "./types";
import ErrorCheck from "./ErrorCheck";

const ModalAdd: React.FC<Foods> = ({ rows, setter, setOpenRow}) => {
  const [name, setName] = useState("");
  const [type, setType] = useState("");
  const [price, setPrice] = useState("");
  const [quantity, setQuantity] = useState("");
  const [error_msg, setErrorMsg] = useState("");

  const handleAddProduct = () => {
    if (ErrorCheck({name, type, price, quantity, setErrorMsg})){
        return;
    }

    setter([...rows, {name : name, type : type, 
        price : parseFloat(price), quantity : parseFloat(quantity), 
        id: rows.length + 1,
        availability: parseFloat(quantity) > 0}]);
    setOpenRow(false);
    setErrorMsg("");
  };

  return (
      <>
      <Stack sx = {{width : '100%'}} spacing={7}>
      {error_msg ? <Alert severity="error">{error_msg}</Alert> : null}
          <TextField
            id="name"
            label="Name"
            variant="outlined"
            value={name}
            onChange={(e) => setName(e.target.value)}
          />
          <TextField
            id="type"
            label="Type"
            variant="outlined"
            value={type}
            onChange={(e) => setType(e.target.value)}
          />
          <TextField
            id="price"
            label="Price"
            variant="outlined"
            type="number"
            value={price}
            onChange={(e) => setPrice(e.target.value)}
          />
          <TextField
            id="quantity"
            label="Quantity"
            variant="outlined"
            type="number"
            value={quantity}
            onChange={(e) => setQuantity(e.target.value)}
          />
          <Button variant="contained" color="primary" onClick={handleAddProduct}>Add Product</Button>
          <Button onClick={() => setOpenRow(false)}>Close</Button>
          </Stack>
      </>

  );
}

export default ModalAdd;