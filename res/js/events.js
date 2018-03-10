
var type = urlParam('type');

var app;
var electronInterval;
if(type == config.firstApp.url)
    app = new FirstApp();
else if(type == config.secondApp.url)
    app = new SecondApp();
else 
    app = new Selecter();

function unbindEvents ()
{
    app.stop();
    clearInterval(electronInterval);
}

function  bindEvents ()
{
    app.start();
    
    
    if(isElectron())
    {
        const electron = require('electron');
        setInterval(() => electron.ipcRenderer.send('ping'), 10000);
    }

}

frontEnd.onEnd(unbindEvents);

setLang(selectedLang);

setTimeout(bindEvents, 10);

var timeoutRestart;

function restart()
{
    app.restart();
    $('#restartModal').modal('hide');

    return false;
}

function cancelRestart()
{
    $('#restartModal').modal('hide');
    
    
    return false;
}

$('#restartOK').on('click', restart);
$('#restartKO').on('click', cancelRestart);



$('#restartGame').on('click', function() { $('#restartModal').modal('show'); timeoutRestart = setTimeout(cancelRestart, 10000); return false } );
$('#restartModal').on('hide.bs.modal', function () { console.log('hello'); clearTimeout(timeoutRestart); });


var copyrightRestart;

function closeCopyright()
{
    $('#copyright').fadeOut(500);
    clearTimeout(copyrightRestart);
}

function goToCopyright()
{
    $('#copyright').fadeIn(500);
    copyrightRestart = setTimeout(closeCopyright, 15000);
    
    return false;
}

$('#goToCopyright').on('click', goToCopyright);
$('#copyrightQuit').on('click', closeCopyright);





