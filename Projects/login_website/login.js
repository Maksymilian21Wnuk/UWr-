const url = "http://localhost:3000/"


document.getElementById("login-form").addEventListener('submit', async function validatePasswords(e) {
    e.preventDefault();

    const login = document.getElementById("login").value;
    const password = document.getElementById("password").value;
    
    dataToSubmit = JSON.stringify({ login, password });

    var response = await fetch(url + "post-login", {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: dataToSubmit
    });

    if (response.status === 200) {
        alert("Login successful")
        window.location = "logged.html"
    }
    else if (response.status === 400) {
        alert("Invalid login or password")
    }
    }
);