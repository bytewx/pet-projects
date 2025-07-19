import { Play, Pause, SkipBack, SkipForward, Shuffle, Repeat, Volume2, Heart } from "lucide-react";
import { Button } from "@/components/ui/button";
import { Slider } from "@/components/ui/slider";
import { useState } from "react";

const MusicPlayer = () => {
  const [isPlaying, setIsPlaying] = useState(false);
  const [volume, setVolume] = useState([70]);
  const [progress, setProgress] = useState([25]);

  return (
    <div className="h-20 bg-card border-t border-border px-4 flex items-center justify-between">
      <div className="flex items-center min-w-0 w-1/4">
        <div className="w-14 h-14 bg-accent rounded-md mr-3 flex-shrink-0"></div>
        <div className="min-w-0">
          <p className="text-sm font-medium text-foreground truncate">Song Title</p>
          <p className="text-xs text-muted-foreground truncate">Artist Name</p>
        </div>
        <Button variant="ghost" size="sm" className="ml-2 text-muted-foreground hover:text-foreground">
          <Heart className="w-4 h-4" />
        </Button>
      </div>

      <div className="flex flex-col items-center w-2/4 max-w-2xl">
        <div className="flex items-center gap-2 mb-2">
          <Button variant="ghost" size="sm" className="text-muted-foreground hover:text-foreground">
            <Shuffle className="w-4 h-4" />
          </Button>
          <Button variant="ghost" size="sm" className="text-muted-foreground hover:text-foreground">
            <SkipBack className="w-4 h-4" />
          </Button>
          <Button 
            size="sm" 
            className="w-8 h-8 rounded-full bg-primary hover:bg-primary/90 text-primary-foreground"
            onClick={() => setIsPlaying(!isPlaying)}
          >
            {isPlaying ? <Pause className="w-4 h-4" /> : <Play className="w-4 h-4 ml-0.5" />}
          </Button>
          <Button variant="ghost" size="sm" className="text-muted-foreground hover:text-foreground">
            <SkipForward className="w-4 h-4" />
          </Button>
          <Button variant="ghost" size="sm" className="text-muted-foreground hover:text-foreground">
            <Repeat className="w-4 h-4" />
          </Button>
        </div>
        
        <div className="flex items-center gap-2 w-full">
          <span className="text-xs text-muted-foreground">1:23</span>
          <Slider
            value={progress}
            onValueChange={setProgress}
            max={100}
            step={1}
            className="flex-1"
          />
          <span className="text-xs text-muted-foreground">3:45</span>
        </div>
      </div>

      <div className="flex items-center justify-end w-1/4">
        <Button variant="ghost" size="sm" className="text-muted-foreground hover:text-foreground mr-2">
          <Volume2 className="w-4 h-4" />
        </Button>
        <Slider
          value={volume}
          onValueChange={setVolume}
          max={100}
          step={1}
          className="w-24"
        />
      </div>
    </div>
  );
};

export default MusicPlayer;