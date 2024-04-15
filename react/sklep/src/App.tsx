import Header from './components/Header';
import MyTable from './components/Table';
import { GridColDef } from '@mui/x-data-grid';
import { Food } from './components/types';
import { Box } from '@mui/material';

const columns: GridColDef[] = [
  { field: 'name', headerName: 'Product name', width: 150, type: 'string'},
  { field: 'type', headerName: 'Type', width: 130 , type : 'string'},
  { field: 'price', headerName: 'Price', width: 90, type: 'number', valueFormatter: (params) => `${params} USD` },
  {
    field: 'availability',
    headerName: 'Availability',
    type: 'boolean',
    width: 160,
  },  
  {
    field: 'quantity',
    headerName: 'Quantity',
    type: 'number',
    width: 90,
  },

];


const foods: Food[] = [
  { id: 1, name: 'Apple', type: 'fruit', price: 1.5, availability: true, quantity: 10 },
  { id: 2, name: 'Banana', type: 'fruit', price: 0.8, availability: true, quantity: 15 },
  { id: 3, name: 'Carrot', type: 'vegetable', price: 0.6, availability: true, quantity: 20 },
  { id: 4, name: 'Spinach', type: 'vegetable', price: 1.2, availability: false, quantity: 0 },
  { id: 5, name: 'Tomato', type: 'fruit', price: 0.9, availability: false, quantity: 0 },
  { id: 6, name: 'Potato', type: 'vegetable', price: 0.7, availability: false, quantity: 0 },
  { id: 7, name: 'Broccoli', type: 'vegetable', price: 1.4, availability: true, quantity: 7 },
  { id: 8, name: 'Lettuce', type: 'vegetable', price: 1.0, availability: true, quantity: 14 },
  { id: 9, name: 'Orange', type: 'fruit', price: 1.3, availability: false, quantity: 0 },
  { id: 10, name: 'Cucumber', type: 'fruit', price: 0.6, availability: true, quantity: 16 },
  { id: 11, name: 'Onion', type: 'vegetable', price: 0.5, availability: true, quantity: 22 },
  { id: 12, name: 'Strawberry', type: 'fruit', price: 2.0, availability: true, quantity: 9 },
  { id: 13, name: 'Blueberry', type: 'fruit', price: 2.5, availability: true, quantity: 11 },
  { id: 14, name: 'Grapes', type: 'fruit', price: 1.8, availability: true, quantity: 13 },
  { id: 15, name: 'Pineapple', type: 'fruit', price: 2.2, availability: true, quantity: 6 },
  { id: 16, name: 'Mango', type: 'fruit', price: 1.9, availability: true, quantity: 17 },
  { id: 17, name: 'Watermelon', type: 'fruit', price: 1.7, availability: true, quantity: 19 },
  { id: 18, name: 'Kiwi', type: 'fruit', price: 1.6, availability: true, quantity: 21 },
  { id: 19, name: 'Avocado', type: 'fruit', price: 2.3, availability: true, quantity: 23 },
  { id: 20, name: 'Peach', type: 'fruit', price: 1.7, availability: false, quantity: 0 }
];


function App() {
  return (
    <Box>
      <Header username="John Doe" shop_name='Amazing food store' />      
      <MyTable rows = {foods} columns={columns}/>
    </Box>
  );  
}

export default App;
