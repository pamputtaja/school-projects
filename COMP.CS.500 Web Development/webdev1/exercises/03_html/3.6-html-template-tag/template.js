const submit = document.getElementById("submit");

submit.addEventListener("click", function(event) {
    event.preventDefault();

    const form = new FormData(event.target);
    const template = document.getElementById("contact-template");
    const contactinfo = document.importNode(template.contentEditable, true);

    contactinfo.querySelector("h2").textContent = form.get("name");
    contactinfo.querySelector("email").textContent = form.get("email");
    contactinfo.querySelector("homepage").textContent = form.get("homepage");

    document.getElementById("contacts").appendChild(contactinfo);
})
