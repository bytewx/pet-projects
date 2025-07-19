import { Play } from "lucide-react";
import { Button } from "@/components/button";
import { Card } from "@/components/ui/card";

interface AlbumCardProps {
  title: string;
  artist: string;
  imageUrl?: string;
  type?: string;
}

const AlbumCard = ({ title, artist, imageUrl, type = "Album" }: AlbumCardProps) => {
  return (
    <Card className="bg-card hover:bg-accent/50 transition-all duration-300 p-4 group cursor-pointer">
      <div className="relative mb-4">
        <div className="aspect-square bg-accent rounded-md overflow-hidden">
          {imageUrl ? (
            <img src={imageUrl} alt={title} className="w-full h-full object-cover" />
          ) : (
            <div className="w-full h-full bg-gradient-to-br from-accent to-muted"></div>
          )}
        </div>
        <Button
          size="sm"
          className="absolute bottom-2 right-2 w-12 h-12 rounded-full bg-primary hover:bg-primary/90 text-primary-foreground shadow-lg opacity-0 group-hover:opacity-100 transform translate-y-2 group-hover:translate-y-0 transition-all duration-300"
        >
          <Play className="w-4 h-4 ml-0.5" />
        </Button>
      </div>
      <div className="space-y-1">
        <h3 className="font-semibold text-foreground truncate">{title}</h3>
        <p className="text-sm text-muted-foreground truncate">{type} • {artist}</p>
      </div>
    </Card>
  );
};

export default AlbumCard;