const loginpasRegex = /^[a-zA-Z0-9_]+$/;
const minLength = 4;
const maxLength = 20;
const url = "http://localhost:3000/"

function validate_logpas(val){
    if (val.length < minLength || val.length > maxLength) {
        return false; 
    }
    else if (!loginpasRegex.test(val)) {
        return false;
    }
    return true
    }



document.getElementById("process_form").addEventListener('submit', async function validatePasswords(e) {
    e.preventDefault();
    const password = document.getElementById("password").value;
    const verifyPassword = document.getElementById("password-verify").value;
    const email = document.getElementById("email").value;
    const login = document.getElementById("login").value;

    if (!validate_logpas(login)) {
        alert("Login should be between 4 and 20 characters long and contain only letters, numbers, and underscores.");
    } else if (!validate_logpas(password)) {
        alert("Password should be between 4 and 20 characters long and contain only letters, numbers, and underscores.");
    } else if (email === "" || login === "" || password === "" || verifyPassword === "" ) {
        alert("Please fill out all fields");
    } else if (password !== verifyPassword) {
        alert("Passwords do not match");
    } else {
        const dataToSubmit = JSON.stringify({ email, login, password });

        var response = await fetch(url + "post-account", {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: dataToSubmit
        });

    }
    document.getElementById("process_form").reset();
});