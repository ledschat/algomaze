function Selecter()
{
    ///////////////////////////////////////////////
    // Private
    //////////////////////////////////////////////
    
    var screen      = new ScreenChanger();
    
    var self        = this;
    
    
    function startSelecter()
    {
        $('#firstAppLink').attr("href", "?type=" + config.firstApp.url);
        $('#secondAppLink').attr("href", "?type=" + config.secondApp.url);
    }



    ///////////////////////////////////////////////
    // Public
    //////////////////////////////////////////////
    
    self.start = function()
    {
        screen.addStartCallback("selecterScreen", startSelecter); 

        screen.next('selecterScreen');
        
    };
    
    self.stop = function()
    {
        screen.stop();
    };
}


