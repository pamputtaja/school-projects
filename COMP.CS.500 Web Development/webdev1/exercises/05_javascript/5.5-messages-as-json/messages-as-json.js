document.addEventListener('userDataReady', (event) => {
    const jsonData = JSON.parse(event.detail.jsonText);
    const template = document.getElementById("user-card-template");
    const contacts = document.getElementById('contacts');

    jsonData.forEach((data) => {
        const info = document.importNode(template.content, true);
        
        const imgSrc = info.querySelector('img').src;
        const imgAlt = info.querySelector('img').alt;
        const name = info.querySelector('h1');
        const email = info.querySelector('.title.email');
        const phone = info.querySelector('p.phone span');
        const streetAddress = info.querySelector('.address > p:nth-child(1)');
        const zipCode_city = info.querySelector('.address > p:nth-child(2)');
        const country = info.querySelector('.address > p:nth-child(3)');
        const homePage = info.querySelector("p.homepage a");

        imgSrc.textContent = data.avatar;
        imgAlt.textContent = data.firstName + ' ' + data.lastName;
        name.textContent = data.firstName + ' ' + data.lastName;
        email.textContent = data.email;
        phone.textContent = data.phoneNumber;
        streetAddress.textContent = data.address.streetAddress;
        zipCode_city.textContent = data.address.zipCode + ' ' + data.address.city;
        country.textContent = data.address.country;
        homePage.setAttribute('href', data.homepage.url);
        
        contacts.appendChild(info);      
    });
});

document.addEventListener("DOMContentLoaded", function() {
    fetchUserData();
  });

