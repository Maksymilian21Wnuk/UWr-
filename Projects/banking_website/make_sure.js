const url = "http://localhost:3000/";
const fakeVal = 42;

document.getElementById('transferForm').addEventListener('submit', async function(event) {
    event.preventDefault();

    var recipientName = document.getElementById('recipientName').value;
    var recipientIBAN = document.getElementById('recipientIBAN').value;
    var transferValue = document.getElementById('transferValue').value;
    var message = document.getElementById('message').value;

    var confirmationMessage = `
    <h2>Are you sure you want to make the following transfer?</h2>
    <p>Recipient Name: ${recipientName}</p>
    <p>Recipient IBAN: ${recipientIBAN}</p>
    <p>Transfer Value: ${transferValue}</p>
    <p>Message: ${message}</p>
    <button id="confirmButton">Confirm</button>
    `;

    var confirmationDiv = document.getElementById('sure');
    confirmationDiv.innerHTML = confirmationMessage;

    document.getElementById('confirmButton').addEventListener('click', async function() {
        var response = await fetch(url + "post-val", {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                name: recipientName,
                iban: fakeVal,
                value: transferValue,
                message: message
            })
        });
    });
    
});
