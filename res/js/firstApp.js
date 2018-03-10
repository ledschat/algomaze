

function FirstApp()
{
    ///////////////////////////////////////////////
    // Private
    //////////////////////////////////////////////
    
    var currentCell = 1;
    var mode        = 0;
    var screen      = new ScreenChanger();
    var timeout     = new Timeout();
    
    var animation   = new AppealingAnimation(lang[selectedLang].firstApp.welcome, '#firstScreenTitle');
    
    var highlighted = 0;
    
    var orders      = [];

    var victTimeout = undefined;
    var aliveTimeout = undefined;
    var phiTimeout   = undefined;
    
    var conn         = undefined;
    
    var upButton     = undefined;
    var leftButton   = undefined;
    var rightButton  = undefined;
    
    var okButton     = undefined;
    
    var self        = this;
    
    
    // Event functions
    
    function sendAlive()
    {
        webrtc.send({cmd : "alive"});
        
        aliveTimeout = setTimeout(sendAlive, 3000);
    }

    function keyReceiver(key)
    {
        var c, t, o;
        
        timeout.update();
       
        switch(key.key)
        {
            case "ArrowLeft":
                var audio = new Audio('frontend/sounds/bip4.wav');
                audio.play();
                c = 'imgDirectionLeftRound';
                t = lang[selectedLang].directions.left;
                o = directions.left;
                break;
                
            case "ArrowRight":
                var audio = new Audio('frontend/sounds/bip4.wav');
                audio.play();
                c = 'imgDirectionRightRound';
                t = lang[selectedLang].directions.right;
                o = directions.right;
                break;
                
            case "ArrowUp":
                var audio = new Audio('frontend/sounds/bip4.wav');
                audio.play();
                c = 'imgDirectionForward';
                t = lang[selectedLang].directions.forward;
                o = directions.forward;
                break;
                
            case "Enter":
                
                if(!mode)
                    validation();
                
                    
                return;
                
            default:
                return;
        }
        
        if(mode == 1) return;
       
        var e = $("#cell" + currentCell);
        
        if(currentCell - 1  == orders.length)
        {
            orders.push(o);
            e.children('.cellIcon').addClass('imgDirection');
        }
        else
        {
            orders[currentCell - 1] = o;
            e.children('.cellIcon').removeClass('imgDirectionForward');
            e.children('.cellIcon').removeClass('imgDirectionLeftRound');
            e.children('.cellIcon').removeClass('imgDirectionRightRound');
        }   

        e.children('.cellIcon').addClass(c);
        e.children('.cellText').text(t);
        e.removeClass("cursorCell");
       
        if(currentCell <15)
            currentCell++;
            
        $("#cell" + currentCell).addClass("cursorCell");
       
    }
    
    function cellClick(event)
    {
        var newId = event.target.id;
        
        timeout.update();
        
        if(newId.slice(0, 4) != "cell")
            newId = event.target.parentElement.id;
        
        newId = parseInt(newId.slice(4));
        
        if(orders.length + 1 >= newId)
        {
            $("#cell" + currentCell).removeClass("cursorCell");
            currentCell = newId;
            $("#cell" + currentCell).addClass("cursorCell");
        }
    }
    
    function validation()
    {
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
        timeout.update();
        
        //if(mode === 0)
        {
            //$('#validation').text(lang[selectedLang].stopSim);
            webrtc.send({cmd : "movePuppetAgent", orders: orders});
            
            $("#cell" + currentCell).removeClass('cursorCell');

            $('#validation').prop("disabled", true);

            mode = 1;

            $('#lookModal').modal('show');
            
        }/*
        else
        {
            $('#validation').text(lang[selectedLang].startSim);
            webrtc.send({cmd : "restartPuppetAgent"});
            $("#cell" + currentCell).addClass('cursorCell');
            $('#agentKOModal').modal('hide');
            highlight(0);
            
        }
        */
            
        //mode = 1 - mode;
    }
    
        
    function help()
    {
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
        timeout.update();
        
        $('#firstHelpModal').modal('show');
        
        webrtc.send({cmd: "pathPuppetAgent"});
    }
    
    
    function restartGame()
    {
        timeout.update();
        
        webrtc.send({cmd : "restartPuppetAgent"});
        $("#cell" + currentCell).addClass('cursorCell');
        //$('#validation').text(lang[selectedLang].startSim);

        $('#validation').prop("disabled", false);

        $('#cell' + highlighted).addClass('fadingCell');
        
        setTimeout(highlight.bind(undefined, 0), 2000);
        
        mode = 0;
        $("#textCorrect").css('color', '#E85A5A');
        $("#textCorrect").fadeIn(200).fadeOut(200).fadeIn(200).fadeOut(200).fadeIn(200).fadeOut(200).fadeIn(200, function() { $("#textCorrect").css('color', 'white'); });
    }
    
    
    // Transition functions
    
    
    function startAppealing()
    {
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
            
        timeout.stop();
        //appeal.start();
        
        animation.start();
        
        
        $('#startDebut').on('click',  screen.bindStartButton('buttonScreen', 'fr'));
        $('#startStart').on('click',  screen.bindStartButton('buttonScreen', 'en'));
        $('#startInizio').on('click', screen.bindStartButton('buttonScreen', 'it'));
        
        $('#restartDiv').fadeOut(200);
        
        $('#withTitle').fadeOut(200);
        $('#withoutTitle').show(200);

        
    }
    
    function stopAppealing()
    {
        animation.stop();
        
        $('#startDebut').unbind('click');
        $('#startStart').unbind('click');
        $('#startInizio').unbind('click');
        
        $('#restartDiv').fadeIn(200);
        
    }
    
    function startButton()
    {
        sendAlive();
        
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
            
        timeout.start();
        $('#contFirstAppInstruct').on('click', screen.bindNext('instructionsScreen'));
        
    }
    
    function stopButton()
    {
        $('#contFirstAppInstruct').unbind('click');
        
        clearTimeout(aliveTimeout);
    }
    
        
    function startInstructions()
    {
        sendAlive();
        
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
            
        $('#startFirstGame').on('click', screen.bindNext('gameScreen'));

        timeout.start();
                
        $('#withTitle').fadeIn(200);
        $('#withoutTitle').hide();
    
    }
    
    function stopInstructions()
    {
        $('#startFirstGame').unbind('click'); 
        
        clearTimeout(aliveTimeout);
    }
    
    function startGame()
    {
        sendAlive();
        
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
                    
        // Reset config
        orders = [];
        currentCell = 1;
        
        
        var elems = $(".cellIcon");
        
        for(var i = 1; i < elems.length; i++)
        {
            var el = elems[i];
            $(el).removeClass('imgDirection');
            $(el).removeClass('imgDirectionForward');
            $(el).removeClass('imgDirectionLeftRound');
            $(el).removeClass('imgDirectionRightRound');
        }
        
        elems = $(".cellText");
        
        for(var i= 1; i < elems.length; i++)
        {
            var el = elems[i];
            $(el).text('');
        }
        
        highlight(0);
        
                
        $("#cell" + currentCell).addClass('cursorCell');
        $('#validation').text(lang[selectedLang].startSim);
        $('#validation').prop("disabled", false);
        mode = 0;
        
        
        $('.cell').on('click', cellClick);
        $('#validation').on('click', validation);
        
        $('#agentKOValidation').on('click', function() { $('#agentKOModal').modal('hide')} );
        $('#agentKOModal').on('hidden.bs.modal', restartGame);
        
        $(document).on('keydown', keyReceiver); 
        
        $('#firstGameHelp').on('click', help);
        $('#firstGameHelp').hide();       
       
        
        timeout.start();
       
        if(conn.connected)
        {
            okButton.open();
            upButton.open();
            leftButton.open();
            rightButton.open();
        }
        else
        {
            if(phiTimeout)
                clearTimeout(phiTimeout);
            phiTimeout = setTimeout(phidgetConnection, 1000);
        }
    }
    
    function stopGame()
    {
        $('.cell').unbind('click');
        $('#validation').unbind('click');
        
        $('#firstHelpModal').modal('hide');
        $('#lookModal').modal('hide');
        
        $(document).unbind('keydown');
        
        $('#agentKOModal').modal('hide');
        $('body').removeClass('modal-open'); 
        $('.modal-backdrop').remove();
        
        $('#agentKOValidation').unbind('click');
        $('#agentKOModal').unbind('hidden.bs.modal');
       
        
        $("#cell" + currentCell).removeClass('cursorCell');

        webrtc.send({cmd : "restartPuppetAgent"});
        
        clearTimeout(aliveTimeout);
        
        if(conn.connected)
        {
           okButton.close();
           upButton.close();
           leftButton.close();
           rightButton.close();
        }
        else
        {
            if(phiTimeout)
                clearTimeout(phiTimeout);
            phiTimeout = setTimeout(phidgetConnection, 1000);
        }
    }

    function startVictory()
    {
        sendAlive();
        
        $('#endFirstGame').on('click', screen.bindNext('appealingScreen'));

        timeout.start();
    }

    
    function stopVictory()
    {
        $('#endFirstGame').unbind('click');
        
        clearTimeout(aliveTimeout);
    }
    
    
    // WebRTC functions
    
    
    function onData(d)
    {
        timeout.update();
        
        if(d.cmd == 'puppetKO')
        {
            $('#lookModal').modal('hide');
            $('#textError').text(lang[selectedLang].errorWhy[d.reason]);
            $('#agentKOModal').modal('show');
            $('#firstGameHelp').show();
            
            highlight(highlighted + 1);
            
            var audio = new Audio('frontend/sounds/error.wav');
            audio.play();

        }
        else if(d.cmd == 'puppetOK')
        {
            $('#lookModal').modal('hide');
            screen.next('victoryFirstAppScreen');
            
            var audio = new Audio('frontend/sounds/victory.wav');
            audio.play();
        }
        else
        {
            var c = orders.length - d.remaining;
            highlight(c);
        }
    }
    

    // Utility functions
    

    function highlight(c)
    {
        if(c == highlighted) return;
        
        if(highlighted != 0)
        {
            $('#cell' + highlighted).removeClass('highlightCell');
            highlighted = 0;
        }
       
        if(c != 0) 
        {
            $('#cell' + c).addClass('highlightCell');
            highlighted = c;
        }
    }
    
    function phidgetCallback(ch, key)
    {
        return function()
        {
            console.log(key);
            if(ch.getState())
                keyReceiver({key : key});
        }
    }
    
    function phidgetConnection()
    {
        phiTimeout = setTimeout(phidgetConnection, 4000);
        
        conn.connect().then(function () 
		{
		    okButton = new jPhidgets.DigitalInput();
		    upButton = new jPhidgets.DigitalInput();
		    leftButton = new jPhidgets.DigitalInput();
		    rightButton = new jPhidgets.DigitalInput();
		    
		    okButton.setChannel(0);
		    upButton.setChannel(2);
		    leftButton.setChannel(3);
		    rightButton.setChannel(1);
		    
		    okButton.onStateChange    = phidgetCallback(okButton, "Enter");
		    upButton.onStateChange    = phidgetCallback(upButton, "ArrowUp");
		    leftButton.onStateChange  = phidgetCallback(leftButton, "ArrowLeft");
		    rightButton.onStateChange = phidgetCallback(rightButton, "ArrowRight");
		   
		    clearTimeout(phiTimeout);
			
		}).catch(function (err) {
		});
    }


    ///////////////////////////////////////////////
    // Public
    //////////////////////////////////////////////
    
    self.start = function()
    {
        screen.addStartCallback("appealingScreen", startAppealing); 
        screen.addStopCallback("appealingScreen", stopAppealing); 
        
        screen.addStartCallback("buttonScreen", startButton); 
        screen.addStopCallback("buttonScreen", stopButton); 
        
        screen.addStartCallback("gameScreen", startGame); 
        screen.addStopCallback("gameScreen", stopGame); 
        
        screen.addStartCallback("instructionsScreen", startInstructions); 
        screen.addStopCallback("instructionsScreen", stopInstructions); 
        
        screen.addStartCallback("victoryFirstAppScreen", startVictory); 
        screen.addStopCallback("victoryFirstAppScreen", stopVictory); 
        
        

        screen.next(config.firstApp.defaultScreen);
        
        webrtc.onData(onData);
        
        timeout.setRedirect(function () { screen.next(config.firstApp.defaultScreen); } );
        
        $('#firstWelcomeSentence').show();

        conn = new jPhidgets.Connection('ws://localhost:10000/phidgets');
        phiTimeout = setTimeout(phidgetConnection(), 1000);

        
    };
    
    self.stop = function()
    {
        screen.stop();
        
        clearTimeout(phiTimeout);
    };
    
    self.restart = function()
    {
        screen.next(config.firstApp.defaultScreen);
    }
}



