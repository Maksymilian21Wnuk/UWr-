import AppBar from '@mui/material/AppBar';
import Toolbar from '@mui/material/Toolbar';
import Typography from '@mui/material/Typography';
import IconButton from '@mui/material/IconButton';
import AccountCircle from '@mui/icons-material/AccountCircle';
import Tooltip from '@mui/material/Tooltip';
import LocalGroceryStoreIcon from '@mui/icons-material/LocalGroceryStore';
import { Icon } from '@mui/material';

interface HeaderProps {
    username: string;
    shop_name : string;
}

const Header:React.FC<HeaderProps> = ({ username, shop_name }) => {
  return (
    <AppBar position="sticky">
      <Toolbar>
        <Typography variant="h6" component="div" sx={{ flexGrow: 1 }}>
        {shop_name}

        <Icon>
          <LocalGroceryStoreIcon />
        </Icon>

        </Typography>
        {//<Box
           // component="img"
            //src="https://www.creativefabrica.com/wp-content/uploads/2019/02/Online-shop-shopping-shop-logo-by-DEEMKA-STUDIO-1.jpg"
            //sx = {{width: 50, height: 50}}
        ///>
      }
        <Tooltip title={username} arrow>
          <IconButton color="inherit">
            <AccountCircle />
          </IconButton>
        </Tooltip>
      </Toolbar>
    </AppBar>
  );
};

export default Header;