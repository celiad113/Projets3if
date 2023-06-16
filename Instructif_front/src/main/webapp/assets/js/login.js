$(document).ready(function() {
    var checkedValue = "eleve";
    $('input[name="accountOption"]').change(function() {
        checkedValue = $('input[name="accountOption"]:checked').val();
        console.log("Checked value: " + checkedValue);
    });
    // Handle form submission
    $('#bouton-connexion').click(function(e) {
        e.preventDefault(); // Prevent the form from submitting normally

        // Get the form values
        var email = $('#login').val();
        var password = $('#password').val();

        var data = {
            email : email,
            password : password
        }

        var hasEmptyField = Object.values(data).some(function(value) {
            return value === '';
        });

        if(hasEmptyField)
        {
            var errorMessage = $('<p>').text(`Tous les champs sont à remplir obligatoirement`).css('color', 'var(--bs-warning)');
            $('#error-message').empty().append(errorMessage);
            return;
        }

        // Create an AJAX request
        $.ajax({
            type: 'POST',
            url: `action-servlet?todo=connexion-${checkedValue}`, // Replace with the correct URL to your Java EE servlet
            data: {
                login: email,
                password: password
            },
            success: function(response) {
                $('#error-message').empty();

                var propertyNames = Object.keys(response);
                console.log(response)
                if(response.connexion === true){
                    if(propertyNames[1] === "eleve"){
                        window.location.href = 'demandeDeCours.html'
                        console.log(`Authentication : ${response.eleve}`)
                    }
                    else if (propertyNames[1] === "intervenant"){
                        console.log(`Intervenant ${response.intervenant.prenom} connecté`);
                        window.location.href = 'espace-intervenant.html'
                    }
                }
                else{
                    var errorMessage = $('<p>').text('Mauvais email ou mot de passe').css('color', 'var(--bs-warning)');
                    $('#error-message').empty().append(errorMessage);
                    $('login').val('')
                    $('password').val('')
                    console.log("Echec de l'authentification")
                }
            },
            error: function() {
                // Handle any errors that occur during the AJAX request
                console.log('Login failed');
            }
        });
    });
});