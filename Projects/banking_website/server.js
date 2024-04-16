const express = require('express');
const cors = require('cors');
const app = express();
const port = 3000;

app.use(cors());

app.use(express.static('public'));
app.use(express.json());

app.post('/post-val', (req,res) => {
    const {name, iban, value, message} = req.body; 
    console.log(name, iban, value, message);
    if (!name || !iban || !value) { 
      return res.status(400).json({status: 'failed'}); 
    }
    res.status(200).json({status: 'success'}); 
});

app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});