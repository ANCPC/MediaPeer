async function login()
{
    const username =
        document.getElementById("username").value;

    const password =
        document.getElementById("password").value;

    const response =
        await fetch("/api/login",
        {
            method:"POST",

            headers:
            {
                "Content-Type":"application/json"
            },

            body:JSON.stringify(
            {
                username:username,
                password:password
            })
        });

    const result =
        await response.json();

    alert(result.message);
}