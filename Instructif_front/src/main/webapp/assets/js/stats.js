$(document).ready(function() {

    var mapContainer = document.getElementById("etablissementsList");
    var mapContainer2 = document.getElementById('lowIpsList');

    mapContainer.style.width = '100%';
    mapContainer.style.height = '600px';

    mapContainer2.style.width = '100%';
    mapContainer2.style.height = '600px';

    const mapListeEtablissements = new ol.Map({
        target: mapContainer,
        layers: [
            new ol.layer.Tile({
                source: new ol.source.OSM(),
            }),
        ],
        view: new ol.View({
            center: [0, 0],
            zoom: 2,
        }),
    });

    const mapIPSBas = new ol.Map({
        target: mapContainer2,
        layers: [
            new ol.layer.Tile({
                source: new ol.source.OSM(),
            }),
        ],
        view: new ol.View({
            center: [0, 0],
            zoom: 2,
        }),
    });

    // Define the extent of France
    var franceExtent = ol.proj.transformExtent([-5.0, 41.0, 9.5, 51.1], 'EPSG:4326', 'EPSG:3857');

    // Zoom the mapListeEtablissements to France
    mapListeEtablissements.getView().fit(franceExtent, { size: mapListeEtablissements.getSize(), padding: [10, 10, 10, 10] });

    // Zoom the mapIPSBas to France
    mapIPSBas.getView().fit(franceExtent, { size: mapIPSBas.getSize(), padding: [10, 10, 10, 10] });

    $.ajax({
        type: 'GET',
        url: 'action-servlet?todo=stats', // Replace with the correct URL to your Java EE servlet
        data: {
            todo: 'stats'
        },
        dataType: 'json'
    })
        .done(function(response) {
            console.log('Response', response);

            $('#elevesInscrits').html(response.nbEleve);
            $('#coursAujd').html(response.nbCours);
            $('#demandesSoutien').html(response.nbDemandes);
            $('#ipsBas').html(response.nbIPS);
            $('#etabEleves').html(response.etabEleves);

            var etablissements = response.etablissements;
            var lowIps = response.lowIps;

            pinEtablissements(etablissements, mapListeEtablissements);
            pinEtablissements(lowIps, mapIPSBas);

        })
        .fail(function(error) {
            console.log('Error', error);
            alert("Erreur lors de l'appel AJAX");
        })
        .always(function () {

        });

});

function pinEtablissements(etablissementsArray, map){

    // Create a vector source for the pins
    var vectorSource = new ol.source.Vector();

    // Iterate over the etablissementsArray and add pins to the vector source
    etablissementsArray.forEach(function (etablissement) {
        // Extract the coordinates from each etablissement
        var latitude = etablissement.latitude;
        var longitude = etablissement.longitude;

        // Create the pin coordinate
        var pinCoordinate = ol.proj.fromLonLat([longitude, latitude]);

        // Create a feature with the pin coordinate
        var feature = new ol.Feature({
            geometry: new ol.geom.Point(pinCoordinate),
        });

        // Add the feature to the vector source
        vectorSource.addFeature(feature);
    });

    // Create a vector layer with the pin source
    var vectorLayer = new ol.layer.Vector({
        source: vectorSource,
    });

    // Create a style for the pins
    var pinStyle = new ol.style.Style({
        image: new ol.style.Circle({
            radius: 6,
            fill: new ol.style.Fill({
                color: 'rgba(255, 0, 0, 0.5)', // Red color with 50% transparency
            }),
            stroke: new ol.style.Stroke({ color: 'white', width: 2 }),
        }),
    });

    // Set the style for the vector layer
    vectorLayer.setStyle(pinStyle);

    map.addLayer(vectorLayer);
}


