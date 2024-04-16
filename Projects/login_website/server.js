const express = require('express');
const cors = require('cors');
const app = express();
const port = 3000;
const mysql = require('mysql');
const db_action = require('./db_actions');
const argon2 = require('argon2');

const db_connection = mysql.createConnection({
    host: 'localhost',
    user: 'meks',
    password: 'password',
    database: 'logins'
});


app.use(cors());
app.use(express.static('public'));
app.use(express.json());


app.post('/post-account', async (req, res) => {
    const { email, login, password } = req.body;
    console.log(email, login, password);

    try {
        const hashedpswd = await argon2.hash(password);
        console.log(hashedpswd);
        
        if (!email || !login || !password) {
            return res.status(400).json({ status: 'failed' });
        }
        
        db_action.select_all(db_connection);
        db_action.add_user(db_connection, { login, email, hashedpswd });

        res.status(200).json({ status: 'success' });
    } 
    catch (error) {
        console.error("Error hashing password:", error);
        return res.status(500).json({ status: 'error', message: 'Internal server error' });
    }
});

app.post('/post-login', async (req, res) => {
    const { login, password } = req.body;

    db_action.check_password(db_connection, login, (error, storedPassword) => {
        if (error) {
            console.error('Error:', error);
            res.status(500).json({ status: 'error', message: 'Internal server error' });
        } else {
            if (storedPassword) {
                argon2.verify(storedPassword, password)
                    .then(match => {
                        if (match) {
                            console.log('Password match');
                            res.status(200).json({ status: 'success' });
                        } else {
                            res.status(400).json({ status: 'error', message: 'Incorrect password' });
                        }
                    })
                    .catch(err => {
                        console.error('Error verifying password:', err);
                        res.status(500).json({ status: 'error', message: 'Internal server error' });
                    });
            } else {
                res.status(400).json({ status: 'error', message: 'User not found' });
            }
        }
    });
});




app.listen(port, () => {
    console.log(`Server is running on port ${port}`);
});