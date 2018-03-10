
var langRequest = { type: "GET", url: 'frontend/settings/lang.json', async: false };
var lang = JSON.parse($.ajax( langRequest ).responseText);

var configRequest = { type: "GET", url: 'frontend/settings/config.json', async: false };
var config = JSON.parse($.ajax( configRequest ).responseText);


var langs = Object.keys(lang);
var selectedLang = config.defaultLanguage;

var directions = 
{
    forward : 0,
    left : -1,
    right: 1,
    turnAround: 2
};

var state = 
{
    empty :     0,
    full :      1,
    emptyFull : 2
};


if(config.disableMouse)
{
    $(document).bind("contextmenu cut copy", function(e){ e.preventDefault(); });
    $(document).disableSelection();
    $('*').css('cursor', 'none');
}

function resize() 
{
    var ww = $('body').width();
    var maxW = 1920;
    ww = Math.min(ww, maxW);
    var fw = ww * (10 / maxW);
    var fpc = fw * 100 / 16;
    var fpc = Math.round(fpc * 100) / 100;
    $('html').css('font-size', fpc + '%');
}

resize();

$(window).resize(resize);

function urlParam (name)
{
    var results = new RegExp('[\?&]' + name + '=([^&#]*)').exec(window.location.href);
    if (results === null)
       return null;
    
    return results[1] || 0;
}


function setLang (l)
{
   var elems = $("[data-text]");
   selectedLang = l;
   
   for(var i = 0; i < elems.length; i++)
   {
        var t = elems[i].dataset.text.split('/');
        t = t.filter(function(entry) { return entry.trim() !== ''; });
       
        var e = lang[l];
        
        for(var j = 0; j < t.length; ++j)
        {
            if(e === undefined) break;
            e = e[t[j]];
        }
        
        if(e !== undefined)
            elems[i].textContent = e;
            
   }
}

function ScreenChanger ()
{
    var currentScreen = null;
    var screens       = {};
    var changing      = false;

    var self = this;
    
    
    self.addStartCallback = function(screen, callback)
    {
        if(screens[screen] === undefined)
            screens[screen] = {};
            
        screens[screen].start = callback;
    };
    
    self.addStopCallback = function(screen, callback)
    {
        if(screens[screen] === undefined)
            screens[screen] = {};
            
        screens[screen].stop = callback;
    };

    self.next = function(next)
    {
        if(changing) return;
        
        
        if(currentScreen === null)
        {
            currentScreen = next; 
            if(screens[currentScreen] !== undefined && screens[currentScreen].start !== undefined)
                screens[currentScreen].start();
            
            $('#' + currentScreen).show(); 
        }
        else
        {
            changing = true;
            $('#' + currentScreen).fadeOut(250, function() {
                
                if(screens[currentScreen] !== undefined && screens[currentScreen].stop !== undefined)
                    screens[currentScreen].stop();
                    
                currentScreen = next;
                
                if(screens[currentScreen] !== undefined && screens[currentScreen].start !== undefined)
                    screens[currentScreen].start();
                
                $('#' + currentScreen).fadeIn(250, function() { changing = false; } );
            });
        }
       
    };
    
    self.bindNext = function(next)
    {
        return function() { self.next(next) };
    };
    
    
    self.startButton = function(next, l, event) 
    { 
       event.stopPropagation(); 
       setLang(l); 
       self.next(next);
    };
    
    self.bindStartButton = function(next, l)
    {
        return function(event) { self.startButton(next, l, event) };
    };
    
    self.stop = function()
    {
        if(screens[currentScreen] !== undefined && screens[currentScreen].stop !== undefined)
            screens[currentScreen].stop();
            
        screens = {};
        currentScreen = null;
    };


}


function Timeout()
{
    var timeout         = config.timeout * 1000;
    var waitingTimeout  = config.waitingTimeout;
    var cpt             = 0; 
    var handler         = undefined;
    var waitingHandler  = undefined;
    var redirect        = undefined;
    
    var self            = this;
    
    function clearWaiting()
    {
        if(waitingHandler !== undefined)
        {
            clearTimeout(waitingHandler);
            waitingHandler = undefined;
            $('#timeoutModal').unbind('hidden.bs.modal');
            $('#timeoutModal').modal('hide');
        }
    }
    
    
    function waitingCallback()
    {
        
        if(++cpt == waitingTimeout)
        {
           
            clearWaiting();
            if(redirect !== undefined)
                redirect();
        }
        else
            waitingHandler = setTimeout(waitingCallback, 1000);
            
        $('#chrono').text(waitingTimeout - cpt);
    }
    
    function callback()
    {
        $('#timeoutModal').modal('show');
        $('#timeoutModal').on('hidden.bs.modal', self.start);
        cpt = 0;
        
        $('#chrono').text(waitingTimeout - cpt);
        
        handler = undefined;
        waitingHandler = setTimeout(waitingCallback, 1000);
    }
    
    self.setRedirect = function(red)
    {
        redirect = red;
    }
    
    self.start = function()
    {
        clearWaiting();
        
        if(handler != undefined) return;
        
        handler = setTimeout(callback, timeout);
    }
    
    self.stop = function()
    {
        clearWaiting();
        
        if(handler == undefined) return;
        
        clearTimeout(handler);
        handler = undefined;
    }
    
    self.update = function()
    {
        if(handler == undefined) return;
        
        self.stop();
        self.start();
    }
}

function Welcome(id)
{
    var currentWelcome = 0;
    var running = false;
    
    function fadeWelcome()
    {
        if(running)
        {
            $('#welcomeSentence').text(lang[langs[currentWelcome]][id].welcome);
            currentWelcome = (currentWelcome + 1) % langs.length;
            
            $('#welcomeSentence').fadeIn(1000).delay(2000).fadeOut(1000, fadeWelcome);
        }
        else
        {
            $('#welcomeSentence').text(lang[selectedLang][id].welcome);
            $('#welcomeSentence').fadeIn(1000);
            
        }
        
    }
    
    this.start = function()
    {
        currentWelcome = 0;
        running = true;
        fadeWelcome();
    };
    
    this.stop = function()
    {
        running = false;
    };
}


function AppealingAnimation(text, id)
{

    var handler     = undefined;
    var mistakesNb  = 0;
    var mistakes    = "qndsrghbkhlopbilatdgycxche";
    var currentText = "_";
    var currentPos  = 0;
    var correcting  = false;
    var callback    = undefined;
    var running     = false;
    var cpt         = 0;

    var self        = this;
    
    function setAnimateTimeout()
    {
        handler = setTimeout(animate, 100 + Math.ceil( Math.random() * 300 ) );
    }

    function setCursorTimeout()
    {
        handler = setTimeout(animate, 700 );
    }

    function animate()
    {

        if(correcting)
        {
            currentText = currentText.slice(0, -1);
            currentPos--;
            
            if(currentText[currentPos] != text[currentPos])
            {
                correcting = false;
                mistakesNb--;
            }
            
            currentText = currentText.slice(0, -1) + '_';

            setAnimateTimeout();
            cpt = 0;
        }
        else
        {
            if(mistakesNb > 0 && Math.random() < 0.9)
            {
                setAnimateTimeout();
                correcting = true;
                cpt = 0;
            }
            else if(currentPos < text.length)
            {
                var car = text[currentPos];
                var code = text.charCodeAt(currentPos);
                
                if(Math.random() < 0.1)
                {
                    // Upper case.
                    if(code > 64 && code < 91)
                    {
                        car = mistakes[code - 'A'.charCodeAt(0)].toUpperCase();
                        mistakesNb++;
                    }
                    
                    // Lower case
                    if(code > 96 && code < 123)
                    {
                        car = mistakes[code - 'a'.charCodeAt(0)];
                        mistakesNb++;
                    }
                    
                }
                
                setAnimateTimeout();
                if(text[currentPos + 1] == ' ')
                    currentText = currentText.slice(0, -1) + car + ' ';
                else
                    currentText = currentText.slice(0, -1) + car + "_";
                    
                currentPos++;
                cpt = 0;
            }
            else
            {
                if( currentText[currentPos] == '_')
                    currentText = currentText.slice(0, -1) + ' ';
                else
                    currentText = currentText.slice(0, -1) + '_';
                    
                if(++cpt == 20)
                    self.reset();
                
                setCursorTimeout();
            }
            
            
        }
        
        var textAfter = text.slice(currentText.length);
        
        var toPrint = `${currentText}<span style="opacity: 0">${textAfter}</span>`;
        
        $(id).html(toPrint);
    }
    
    self.reset = function()
    {
        cpt = 0;
        currentPos = 0;
        currentText = '_';
        mistakesNb = 0;
        correcting = false;
    }
 
    self.start = function()
    {
        if(running) return;

        running = true;
        self.reset();
        animate();
    }
    
    
    self.stop = function()
    {
        running = false;
        clearTimeout(handler);
        $(id).text(text);
    }
 
}


function isElectron() 
{
    if (typeof require !== 'function') return false;
    if (typeof window !== 'object') return false;
    try 
    {
        const electron = require('electron');
        if (typeof electron !== 'object') return false;
    } 
    catch(e) 
    {
        return false;
    }
    return true;
}



