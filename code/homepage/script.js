function loadNavbar() {
    var navbarContainer = document.getElementById("navbarContainer");
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            navbarContainer.innerHTML = this.responseText;
        }
    };

    xhttp.open('GET', 'navbar.html', true);
    xhttp.send();
};