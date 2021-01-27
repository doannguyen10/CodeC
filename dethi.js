function validate() {
    e = document.getElementsByTagName("input")[0].value;
    c = document.getElementsByTagName("input")[1].value;
    r = document.getElementsByTagName("input")[2].value;
    var re = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    if (!e.match(re)) {
        alert("Email không hợp lệ");
    } else {
        if (c != "") {
            alert("Không được nhập vào ô comment");
        } else if (r != "") {
            alert("Không được nhập vào ô rating");
        }
    }
}