
<a href='?redirect=http://localhost/?secret_token=PASSWORD'>Allowed</a>
<a href='?redirect=http://google.com/?secret_token=PASSWORD'>Disallowed</a>
<a href='?redirect=https://google.com?q=PWNED(Check_The_Referer_TAG)&redirect=http://localhost/?secret_token=PASSWORD'>JS HPP</a>

<?php
if ($_GET['redirect']){
    $redirect_domain = parse_url($_GET['redirect'], PHP_URL_HOST);
    if ($redirect_domain != $_SERVER['SERVER_NAME']){
        die("<br>Just same domain url redirect allowed!");
    }
}
?>


<script>
    var url = new URL(document.URL);
    var redirurl = url.searchParams.get("redirect");
    if (redirurl !== null){
        document.write("You are redirecting...");
        window.location = redirurl;
    }
</script>
