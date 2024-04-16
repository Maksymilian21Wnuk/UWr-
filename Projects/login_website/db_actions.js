
function select_all(db_connection) {
    const query = 'SELECT * FROM users';
    db_connection.query(query, (err, result) => {
        if (err) {
            console.log(err);
        } else {
            console.log(result);
        }
    });
}

function add_user(db_connection, user_obj) {
    const query = 'INSERT INTO users (login, email, password) VALUES (?, ?, ?)';
    const values = [user_obj.login, user_obj.email, user_obj.hashedpswd];

    db_connection.query(query, values, (err, result) => {
    if (err) {
        console.log(err);
    } else {
        console.log(result);
    }
    });
}

function check_password(db_connection, login, callback) {
    const query = `SELECT password FROM users WHERE login = ? `;
    
    db_connection.query(query, [login], (error, results) => {
        if (error) {
            console.error('Error retrieving password:', error);
            callback(error, null);
        } 
        else {
            if (results.length > 0) {
                const storedPassword = results[0].password;
                callback(null, storedPassword);
            } else {
                console.log('No user found with login:', login);
                callback(null, null);
            }
        }
    });
}


module.exports = {
    select_all,
    add_user,
    check_password
};