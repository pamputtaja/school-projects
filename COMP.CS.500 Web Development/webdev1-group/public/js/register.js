/**
 * TODO: 8.4 Register new user
 *       - Handle registration form submission
 *       - Prevent registration when password and passwordConfirmation do not match
 *       - Use createNotification() function from utils.js to show user messages of
 *       - error conditions and successful registration
 *       - Reset the form back to empty after successful registration
 *       - Use postOrPutJSON() function from utils.js to send your data back to server
 */
const registerationForm = document.getElementById('register-form');

registerationForm.addEventListener('submit', async  (event) => {
    event.preventDefault();

    const name = document.getElementById('name').value;
    const email = document.getElementById('email').value;
    const password = document.getElementById('password').value;
    const passwordConf = document.getElementById('passwordConfirmation').value;

    if ( password !== passwordConf ) {
        createNotification('Passwords do not match', "notifications-container", false);
        return;
    }

    const user = {
        name,
        email,
        password
    };

    try {
        const response = await postOrPutJSON('/api/register', 'POST', user)
        if ( response.status === 201) {
            createNotification('Registration successful', "notifications-container", true);
            registerationForm.reset();
        } else {
            createNotification('Registeration failed', "notifications-container", false)
        }
    } catch (error) {
        createNotification('Error: ' + error.message, "notifications-container", false)
    }
});