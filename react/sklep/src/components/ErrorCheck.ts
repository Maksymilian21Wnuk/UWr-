interface ValCheck {
    name: string;
    type: string;
    price: string;
    quantity: string;
    setErrorMsg: React.Dispatch<React.SetStateAction<string>>;
}


const ErrorCheck = ({ name, type, price, quantity, setErrorMsg } : ValCheck) => {
  if (!name || !type || !price || !quantity || parseFloat(quantity) < 0 || parseFloat(price) < 0){
    if (!name){
        setErrorMsg("Name is required");
    }
    else if (!type){
        setErrorMsg("Type is required");
    }
    else if (!price){
        setErrorMsg("Price is incorrect value");
    }
    else if (!quantity){
        setErrorMsg("Quantity is incorrect value");
    }
    else if (parseFloat(quantity) < 0){ 
        setErrorMsg("Quantity must be greater than 0");
    }
    else if (parseFloat(price) < 0){
        setErrorMsg("Price must be greater than 0");
    }
    return true;
    }
  return false;
}

export default ErrorCheck;