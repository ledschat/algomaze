

function SecondApp()
{
    ///////////////////////////////////////////////
    // Private
    //////////////////////////////////////////////
    
    var screen      = new ScreenChanger();
    var timeout     = new Timeout();
    
    var algorithm   = [];
    var mode        = 0;
    
    var videoTimeout = undefined;
    var victTimeout  = undefined;
    
    var animation   = new AppealingAnimation(lang[selectedLang].secondApp.welcome, '#firstScreenTitle');
    
    var aliveTimeout = undefined;
    
    var nbLines      = 0;
    var webrtc       = new Communication();
    
    var self        = this;
    
    
    var updateInterval = undefined;
    // Event functions
    
    function sendAlive()
    {
        webrtc.send({cmd : "alive"});
        
        aliveTimeout = setTimeout(sendAlive, 3000);
    }

    
    ////////////////////////////////////////////////////////////
    /// \brief Called on the instructions screen when the user click on the first button.
    ///
    ////////////////////////////////////////////////////////////	
    function videoEnded()
    {
        timeout.start();
        
        videoTimeout = setTimeout(function() 
        { 
            $('#videoInstructions').get(0).currentTime = 0;
            $('#videoInstructions').get(0).play();  
            $('#videoInstructionsText').hide();
            videoTimeout = undefined; 
            
        }, 4000);

    }
    
    function videoProgress()
    {
        var e = $('#videoInstructions');
        
        if(!e[0].duration || !e[0].currentTime)
        {
            
            
        }
        else
        {
            var proportion = e[0].currentTime / e[0].duration * 100;
            
            $('#progressBar').css('width', proportion+'%').attr('aria-valuenow', proportion); 

        }
    }
        
        
    ////////////////////////////////////////////////////////////
    /// \brief Called on the instructions screen when the user click on the continue button.
    ///
    ////////////////////////////////////////////////////////////
    function goToGame()
    {
        timeout.update();
        screen.next('secondGameScreen');
    }
    
    ////////////////////////////////////////////////////////////
    /// \brief Called on the game screen when the user click on the new line button.
    ///
    ////////////////////////////////////////////////////////////
    function newLineEvent()
    {
        var audio = new Audio('frontend/sounds/bip4.wav');
        audio.play();
        timeout.update();
        newLine();
        
    }
    
    ////////////////////////////////////////////////////////////
    /// \brief Called on the game screen when the user drop a valid instruction.
    ///
    ////////////////////////////////////////////////////////////
    function setStateInstruction(event, ui)
    {
        var audio = new Audio('frontend/sounds/bip2.wav');
        audio.play();
        timeout.update();
        
        var e = event.target;
        var isFull = $(ui.draggable[0]).hasClass('fullState');
        var isEmpty = $(ui.draggable[0]).hasClass('emptyState');
        
        $(e).removeClass('emptyState');
        $(e).removeClass('fullState');
        $(e).removeClass('emptyFullState');
        
        if(isFull)
            $(e).addClass('fullState');
        else if(isEmpty)
            $(e).addClass('emptyState');
        else
            $(e).addClass('emptyFullState');
        
        var parent = $(e).closest('.instruction')[0];
        updateInstruction(parent);

    }
    
    ////////////////////////////////////////////////////////////
    /// \brief Called on the game screen when the user drop a valid direction.
    ///
    ////////////////////////////////////////////////////////////
    function setDirectionInstruction(event, ui)
    {
        var audio = new Audio('frontend/sounds/bip2.wav');
        audio.play();
        timeout.update();
        
        var e = event.target;
        var id = ui.draggable[0].id;
        
        $(e).removeClass('imgDirectionForward');
        $(e).removeClass('imgDirectionLeft');
        $(e).removeClass('imgDirectionRight');
        $(e).removeClass('imgDirectionTurnAround');

        switch(id)
        {
            case "forwardDirectionInstruction":
                $(e).addClass('imgDirectionForward');
                break;
                
            case "leftDirectionInstruction":
                $(e).addClass('imgDirectionLeft');
                break;
                
            case "rightDirectionInstruction":
                $(e).addClass('imgDirectionRight');
                break;
                
            case "turnAroundDirectionInstruction":
                $(e).addClass('imgDirectionTurnAround');
                break;
        }
        
        var parent = $(e).closest('.instruction')[0];
        updateInstruction(parent);
    }
    
    ////////////////////////////////////////////////////////////
    /// \brief Called on the game screen when the user start the algorithm.
    ///
    ////////////////////////////////////////////////////////////
    function startAlgo()
    {
        
        if(mode === 0)
        {
            $('#startAlgo').text(lang[selectedLang].stopSim); 
            webrtc.send({cmd : "moveFollowingAgent", algorithm : algorithm});
            
            timeout.stop();
            
            var audio = new Audio('frontend/sounds/bip3.wav');
            audio.play();

            $('#lookModal').modal('show');
        }
        else
        {
            $('#startAlgo').text(lang[selectedLang].startSim);
            webrtc.send({cmd : "restartFollowingAgent"});
            
            timeout.update();
            
            var audio = new Audio('frontend/sounds/error.wav');
            audio.play();
        }
            
        mode = 1 - mode;
        
       
    }
    
    ////////////////////////////////////////////////////////////
    /// \brief Called on the game screen when the user is dragging an instruction and is over a valid position.
    ///
    ////////////////////////////////////////////////////////////
    function overState(event, ui)
    {
        console.log('over state')
        timeout.update();
        
        var isFull = $(ui.draggable[0]).hasClass('fullState');
        var isEmpty = $(ui.draggable[0]).hasClass('emptyState');
        var e = event.target;
        
        $(e).removeClass('fullStateHighlight');
        $(e).removeClass('emptyStateHighlight');
        $(e).removeClass('emptyFullStateHighlight');

        if(isFull)
            $(e).addClass('fullStateHighlight');
        else if(isEmpty)
            $(e).addClass('emptyStateHighlight');
        else
            $(e).addClass('emptyFullStateHighlight');
        
    }
    
    ////////////////////////////////////////////////////////////
    /// \brief Called on the game screen whenthe user is dragging an direction and is over a valid position.
    ///
    ////////////////////////////////////////////////////////////
    function overDirection(event, ui)
    {
        timeout.update();
        
        var id = ui.draggable[0].id;
        var e = event.target;
        
        $(e).removeClass('directionForwardHighlight');
        $(e).removeClass('directionLeftHighlight');
        $(e).removeClass('directionRightHighlight');
        $(e).removeClass('directionTurnAroundHighlight');
        
        switch(id)
        {
            case "forwardDirectionInstruction":
                $(e).addClass('directionForwardHighlight');
                break;
                
            case "leftDirectionInstruction":
                $(e).addClass('directionLeftHighlight');
                break;
                
            case "rightDirectionInstruction":
                $(e).addClass('directionRightHighlight');
                break;
                
            case "turnAroundDirectionInstruction":
                $(e).addClass('directionTurnAroundHighlight');
                break;
        }
    }
    
    ////////////////////////////////////////////////////////////
    /// \brief Called on the game screen when the user is dragging an object.
    ///
    ////////////////////////////////////////////////////////////
    function onDrag()
    {
        timeout.update();
        
    }
    
    function startDragSound()
    {
        var audio = new Audio('frontend/sounds/bip1.wav');
        audio.play();
    }
    
    ////////////////////////////////////////////////////////////
    /// \brief Called on the game screen when the user close the game over screen.
    ///
    ////////////////////////////////////////////////////////////
    function restartGame()
    {
        timeout.update();
        
        $('#startAlgo').text(lang[selectedLang].startSim);
        webrtc.send({cmd : "restartFollowingAgent"});
        mode = 1 - mode;
    }
    
    
    function help()
    {
        timeout.update();
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
        $('#fullHelpModal').modal('show');
    }
    
    function helpSymbol()
    {
        timeout.update();
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
        $('#symbolHelpModal').modal('show');
    }

    function closeModal()
    {
        timeout.update();
    }
    
        
    function onStartDrag(event, ui)
    {
        $(event.target).addClass('highlightDrag');
        var audio = new Audio('frontend/sounds/bip1.wav');
        audio.play();
    }
    
    function onStopDrag(event, ui)
    {
       
        var e = event.target;
        $(e).removeClass('emptyState');
        $(e).removeClass('fullState');
        $(e).addClass('emptyFullState');
        $(e).draggable( "destroy" );
        setDragAndDrop();
        
        var parent = $(e).closest('.instruction')[0];
        updateInstruction(parent);
        
        $(event.target).removeClass('highlightDrag');
        var audio = new Audio('frontend/sounds/bip2.wav');
        audio.play();

    }
    
    function firstHelpButton()
    {
        $('#firstHelp').show();
        $('#firstHelpButton').hide();
        $('#secondHelpButton').show();
        
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
    }
    
    function secondHelpButton()
    {
        $('#secondHelp').show();
        $('#secondHelpButton').hide();
        $('#thirdHelpButton').show();
        
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
    }
    
    function thirdHelpButton()
    {
        $('#thirdHelp').show();
        $('#thirdHelpButton').hide();
        $('#fourthHelpButton').show();
        
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
    }
    
    function fourthHelpButton()
    {
        $('#fourthHelp').show();
        $('#fourthHelpButton').hide();
        
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
    }
    
    
    // Transition functions


    function startAppealing()
    {
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
        
        timeout.stop();
        animation.start();
        
        
        $('#restartDiv').fadeOut(200);
        
        $('#startDebut').on('click',  screen.bindStartButton('secondAppButtonScreen', 'fr'));
        $('#startStart').on('click',  screen.bindStartButton('secondAppButtonScreen', 'en'));
        $('#startInizio').on('click', screen.bindStartButton('secondAppButtonScreen', 'it'));
        
        $('#withTitle').hide();
        $('#withoutTitle').show();
    }
    
    function stopAppealing()
    {
        $('#restartDiv').fadeIn(200);
        animation.stop();
        
        $('#startDebut').unbind('click');
        $('#startStart').unbind('click');
        $('#startInizio').unbind('click');
        
       
    }
    
    function startButton()
    {
        sendAlive();
        
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
        
        timeout.start();
        $('#contSecondAppInstruct').on('click', screen.bindNext('secondAppInstructionsScreen'));
        
    }
    
    function stopButton()
    {
        $('#contSecondAppInstruct').unbind('click');
        
        clearTimeout(aliveTimeout);
    }
    
    function startInstructions()
    {
        sendAlive();
        
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();

        $('#videoMp4').attr('src', 'frontend/video/' + selectedLang + '.mp4');
        $('#videoWebm').attr('src', 'frontend/video/' + selectedLang + '.webm');
        $('#videoInstructions').get(0).load(); 
         
        $('#videoInstructions').on('ended', videoEnded);
        updateInterval = setInterval(videoProgress, 100);
        
        $('#progressBar').css('width', '0%').attr('aria-valuenow', 0); 
        
        $('#startSecondGame').on('click', goToGame);
        
        $('#withTitle').show();
        $('#withoutTitle').hide();
        
        timeout.stop();
        
        
        videoTimeout = setTimeout(function() 
        { 
            $('#videoInstructions').get(0).currentTime = 0;
            $('#videoInstructions').get(0).play();  
            $('#videoInstructionsText').hide();
            videoTimeout = undefined; 
            
        }, 4000);
    }
    
    function stopInstructions()
    {
        $('#startSecondGame').unbind('click');
        
        clearInterval(updateInterval);
        $('#videoInstructions').unbind('ended');

        if(videoTimeout != undefined)
            clearTimeout(videoTimeout);
            
         $('#videoInstructionsText').hide();
            
        $('#videoInstructions').get(0).pause();  
        
        clearTimeout(aliveTimeout);
    }
    

    function startGame()
    {
        sendAlive();
        
        var audio = new Audio('frontend/sounds/bip3.wav');
        audio.play();
        
        timeout.start();
         
        // Reset config
        algorithm  = [];
        $("#algorithm").empty();
        
        $('#newLine').show();
        
        nbLines = 0;
        
        newLine();
                
        $('#startAlgo').text(lang[selectedLang].startSim);
        mode = 0;
        
        $('#newLine').on('click', newLineEvent);
        $('#startAlgo').on('click', startAlgo);
        
        $('#agentKOValidation').on('click', function() { $('#agentKOModal').modal('hide')} );
        $('#agentKOModal').on('hidden.bs.modal', restartGame);
        
        $('#secondGameHelp').on('click', help);
        $('#fullHelpModal').on('hidden.bs.modal', closeModal);
        
        $('#symbolHelpButton').on('click', helpSymbol);
        $('#symbolHelpModal').on('hidden.bs.modal', closeModal);
        
        $('#firstHelp').hide();
        $('#secondHelp').hide();
        $('#thirdHelp').hide();
        $('#fourthHelp').hide();
        
        $('#firstHelpButton').show();
        $('#secondHelpButton').hide();
        $('#thirdHelpButton').hide();
        $('#fourthHelpButton').hide();
        
        $('#firstHelpButton').on('click', firstHelpButton);
        $('#secondHelpButton').on('click', secondHelpButton);
        $('#thirdHelpButton').on('click', thirdHelpButton);
        $('#fourthHelpButton').on('click', fourthHelpButton);
        $('#restartTuto').on('click', screen.bindNext('secondAppInstructionsScreen'));
        
        
    }
    
    
    function stopGame()
    {
        $( '.stateInstructionDrag' ).draggable('destroy');
        $( '.directionDrag' ).draggable('destroy');
        
        
        $('#lookModal').modal('hide');
        
        $( '.stateInstructionDrop' ).droppable('destroy');
        $( '.directionDrop' ).droppable('destroy');
        
        $('#startAlgo').unbind('click');
        $('#newLine').unbind('click');
        
        $('#agentKOValidation').unbind('click');
        $('#agentKOModal').unbind('hidden.bs.modal');
        
        $('#secondGameHelp').unbind('click');
        $('#fullHelpModal').unbind('hidden.bs.modal');
        
        $('#symbolHelpButton').unbind('click');
        $('#symbolHelpModal').unbind('hidden.bs.modal');
        
        $('#agentKOModal').modal('hide');
        
        $('#fullHelpModal').modal('hide');
        $('#restartTuto').unbind('click');
        
        webrtc.send({cmd : "restartFollowingAgent"});
        
        $('#firstHelpButton').unbind('click');
        $('#secondHelpButton').unbind('click');
        $('#thirdHelpButton').unbind('click');
        $('#fourthHelpButton').unbind('click');
        
        clearTimeout(aliveTimeout);
        

    }
    
        
    function startVictory()
    {
        sendAlive();
        
        timeout.start();

        $('#endSecondGame').on('click', screen.bindNext('appealingScreen'));
    }

    
    function stopVictory()
    {
        $('#endSecondGame').unbind('click');
        
        clearTimeout(aliveTimeout);
    }

    // Utility functions
    
    function newLine()
    {
        if(nbLines == 4) return;
        
        algorithm.push({state : [state.empty, state.empty, state.empty], direction : directions.forward});
        var ifElseIf = algorithm.length == 1 ? lang[selectedLang].secondApp.if : lang[selectedLang].secondApp.elseif;
        
        var html = `
        <div id="instruction${algorithm.length}" class="instruction">
            <div class="row">
                <div class="col-xs-4 col-xs-offset-3">
                    <div class="emptyFullState forwardCell stateInstructionDrop"></div>
                </div>
            </div>
             <div class="row">
                <div class="col-xs-3 conditionText text-center">
                    ${ifElseIf}
                </div>
                <div class="col-xs-4">
                    <div class="emptyFullState leftCell stateInstructionDrop"></div>
                    <div class="inputAlgorithmTop"></div>
                    <div class="emptyFullState rightCell stateInstructionDrop"></div>
                </div>
                 <div class="col-xs-2 conditionText text-center">
                    ${lang[selectedLang].secondApp.then}
                </div>
                <div class="col-xs-3">
                    <div class="directionDrop imgDirection imgDirectionForward"></div>
                </div>
            </div>
             <div class="row">
                <div class="col-xs-4 col-xs-offset-3">
                    <div class="inputAlgorithmBottom"></div>
                </div>
            </div>
        </div>`;
        
        $("#algorithm").append(html);
        
        setDragAndDrop();
        
        ++nbLines;
        if(nbLines == 4)
            $('#newLine').hide();
    }
    
    function setDragAndDrop()
    {
        $( '.stateInstructionDrag' ).draggable( { opacity: 0.9, helper: "clone",  zIndex: 100, start: startDragSound} );
        
        $( '.stateInstructionDrop' ).droppable( 
        { 
            accept: ".stateInstructionDrag, .stateInstructionDrop",
            classes: { "ui-droppable-hover" : "highlight" }, 
            over : overState,
            drop: setStateInstruction,
            tolerance: 'touch'
        } );
        
        
        
        $( '.directionDrag' ).draggable( { opacity: 0.9, helper: "clone",  zIndex: 100, drag: onDrag, start: startDragSound } );
        
        $( '.directionDrop' ).droppable( 
        { 
            accept: ".directionDrag",
            classes: { "ui-droppable-hover" : "highlight" }, 
            over : overDirection,
            drop: setDirectionInstruction,
            tolerance: 'touch' 
        } );
        
        $( '.stateInstructionDrop.fullState, .stateInstructionDrop.emptyState' ).draggable( 
        { 
            opacity: 0.9,  
            helper: "clone",  
            zIndex: 200, 
            appendTo: 'body',
            start: onStartDrag, 
            drag : onDrag,
            stop: onStopDrag
            
        } );
        
    }

    
    function updateInstruction(parent)
    {
        var instrucId = parseInt(parent.id.slice(11));
        
        var el = [
            $(parent).find('.forwardCell')[0], 
            $(parent).find('.leftCell')[0],
            $(parent).find('.rightCell')[0]
        ];
        
        var s = [state.empty, state.empty, state.empty];
        
        for(var i = 0; i < el.length; ++i)
        {
            if($(el[i]).hasClass('fullState'))
                s[i] = state.full;
            else if($(el[i]).hasClass('emptyFullState'))
                s[i] = state.emptyFull;
            
        }
        
        el = $(parent).find('.directionDrop')[0];
        
        var d = directions.forward;
        
        if($(el).hasClass('imgDirectionRight'))
            d = directions.right;
        else if($(el).hasClass('imgDirectionLeft'))    
            d = directions.left;
        else if($(el).hasClass('imgDirectionTurnAround'))
            d = directions.turnAround;
        
        if(instrucId - 1 < algorithm.length)
        {
            algorithm[instrucId - 1].state = s;
            algorithm[instrucId - 1].direction = d;
        }
        
        setTimeout(setDragAndDrop, 10);
    }
    
    // WebRTC functions
    
    function onData(d)
    {
        timeout.update();
        
        if(d.cmd == 'followingKO')
        {
            $('#lookModal').modal('hide');
            $('#textError').text(lang[selectedLang].errorWhy[d.reason]);
            $('#agentKOModal').modal('show');
            
            var audio = new Audio('frontend/sounds/error.wav');
            audio.play();

           
        }
        else if(d.cmd == 'followingOK')
        {
            $('#lookModal').modal('hide');
            screen.next('victorySecondAppScreen');
           
            var audio = new Audio('frontend/sounds/victory.wav');
            audio.play();

            
        }
    }


    ///////////////////////////////////////////////
    // Public
    //////////////////////////////////////////////
    
    self.start = function()
    {
        screen.addStartCallback("appealingScreen", startAppealing); 
        screen.addStopCallback("appealingScreen", stopAppealing); 
        
        screen.addStartCallback("secondAppButtonScreen", startButton); 
        screen.addStopCallback("secondAppButtonScreen", stopButton); 
        
        screen.addStartCallback("secondAppInstructionsScreen", startInstructions); 
        screen.addStopCallback("secondAppInstructionsScreen", stopInstructions); 
        
        screen.addStartCallback("secondGameScreen", startGame); 
        screen.addStopCallback("secondGameScreen", stopGame);
        
        screen.addStartCallback("victorySecondAppScreen", startVictory); 
        screen.addStopCallback("victorySecondAppScreen", stopVictory); 

        screen.next(config.secondApp.defaultScreen);
        
        webrtc.on('data', onData);
        
        timeout.setRedirect(function () { screen.next(config.secondApp.defaultScreen); } );
        
        $('#secondWelcomeSentence').show();
        

    };
    
    self.stop = function()
    {
        screen.stop();
    };
    
    self.restart = function()
    {
        screen.next('appealingScreen');
    }
}



