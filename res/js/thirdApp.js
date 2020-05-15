

function ThirdApp()
{
    ///////////////////////////////////////////////
    // Private
    //////////////////////////////////////////////
    
    var screen      = new ScreenChanger();
    var timeout     = new Timeout();
    
    var animation   = new AppealingAnimation("Comparez les algorithmes!", '#firstScreenTitle');
    
    var orders      = [];

    var aliveTimeout = undefined;
    
    var algo         = 0;
    
    var self        = this;
    var webrtc      = new Communication();
    
    // Event functions
    
    function sendAlive()
    {
        webrtc.send({cmd : "alive"});
        
        aliveTimeout = setTimeout(sendAlive, 3000);
    }

    
    function startAlgo()
    {
      
        webrtc.send({cmd : "moveSmartAgent"});
        
        timeout.stop();
        
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
        
        $('#lookModal').modal('show');
       
    }
    
    function selectAlgo(id)
    {
        timeout.start();
        timeout.update();
        
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
        
        $('#tablinks' + (algo + 1)).removeClass('tablinksSelected');
        $('#tabcontent' + (algo + 1)).hide();
        algo = id;
        $('#tablinks' + (algo + 1)).addClass('tablinksSelected');
        $('#tabcontent' + (algo + 1)).show();
        
        webrtc.send({cmd : "resetSmartAgent", algorithm : algo});
        
        $('#memoryUsed').text(0);
        $('#timeUsed').text(0);
    }
    
    
    // Transition functions
    
    
    function startAppealing()
    {
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
            
        timeout.stop();
        //appeal.start();
        
        animation.start();
        
        
        $('#startDebut').on('click',  screen.bindStartButton('thirdAppButtonScreen', 'fr'));
        $('#startStart').on('click',  screen.bindStartButton('thirdAppButtonScreen', 'en'));
        $('#startInizio').on('click', screen.bindStartButton('thirdAppButtonScreen', 'it'));
        
      //  $('#restartDiv').fadeOut(200);
        
        $('#withTitle').fadeOut(200);
        $('#withoutTitle').show(200);

        
    }
    
    function stopAppealing()
    {
        animation.stop();
        
        $('#startDebut').unbind('click');
        $('#startStart').unbind('click');
        $('#startInizio').unbind('click');
        
       // $('#restartDiv').fadeIn(200);
        
    }
    
    function startButton()
    {
        sendAlive();
        
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
            
        timeout.start();
        $('#contThirdAppInstruct').on('click', screen.bindNext('thirdGameScreen'));
        
    }
    
    function stopButton()
    {
        $('#contThirdAppInstruct').unbind('click');
        
        clearTimeout(aliveTimeout);
    }
    
    
    function startGame()
    {
        sendAlive();
        
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
        
        $('#withTitle').fadeIn(200);
        $('#withoutTitle').hide();
        
        $('#tablinks1').on('click', selectAlgo.bind(undefined, 0));
        $('#tablinks2').on('click', selectAlgo.bind(undefined, 1));
        $('#tablinks3').on('click', selectAlgo.bind(undefined, 2));
        $('#tablinks4').on('click', selectAlgo.bind(undefined, 3));
        $('#tablinks5').on('click', selectAlgo.bind(undefined, 4));
        
        $('#thirdGameValidation').on('click', startAlgo);
        
        algo = 0;
        webrtc.send({cmd : "resetSmartAgent", algorithm : algo});
        
        $('#memoryUsed').text(0);
        $('#timeUsed').text(0);
    }
    
    function stopGame()
    {
        
        /*
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
        
        $('#firstGameValidation').unbind('click');
		$('#firstGameForward').unbind('click');
		$('#firstGameLeft').unbind('click');
		$('#firstGameRight').unbind('click');
        
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
        
        */
    }
    
    
    // WebRTC functions
    
    
    function onData(d)
    {
        timeout.update();
        
        if(d.cmd == 'smartUpdate')
        {
            $('#memoryUsed').text(d.memory);
            $('#timeUsed').text(d.time);
           

        }
        else if(d.cmd == 'smartDone')
        {
            $('#lookModal').modal('hide');
            var audio = new Audio('frontend/sounds/victory.wav');
            audio.play();
            timeout.start();
        }
    }
    

    ///////////////////////////////////////////////
    // Public
    //////////////////////////////////////////////
    
    self.start = function()
    {
        screen.addStartCallback("appealingScreen", startAppealing); 
        screen.addStopCallback("appealingScreen", stopAppealing); 
        
        screen.addStartCallback("thirdAppButtonScreen", startButton); 
        screen.addStopCallback("thirdAppButtonScreen", stopButton); 
        
        screen.addStartCallback("thirdGameScreen", startGame); 
        screen.addStopCallback("thirdGameScreen", stopGame); 
        

        screen.next(config.thirdApp.defaultScreen);
        
        timeout.setRedirect(function () { screen.next(config.thirdApp.defaultScreen); } );
        
        webrtc.on('data', onData);
        
        $('#thirdWelcomeSentence').show();

        
    };
    
    self.stop = function()
    {
        screen.stop();
    };
    
    self.restart = function()
    {
        screen.next(config.thirdApp.defaultScreen);
    }
}



