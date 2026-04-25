void main()
{
  // economy init
  CreateHive();
  GetHive().InitOffline();

        // comment/remove following 2 lines when not exporting (can cause further issues if you do this each time you start a mission!)
  //GetCEApi().ExportProxyData(vector.Zero, 100000);    // standard map groups (buildings) export, terrain center and radius needs to be specified
  //GetCEApi().ExportClusterData();

  int year, month, day, hour, minute;
  GetGame().GetWorld().GetDate( year, month, day, hour, minute );

  if ( month < 12 )
  {
    year = 2011;
    month = 12;
    day = 1;
    hour = 7;

    GetGame().GetWorld().SetDate( year, month, day, hour, minute );
  }
};

class CustomMission: MissionServer
{
     
  void SetRandomHealth(EntityAI itemEnt)
  {
    if (itemEnt)
    {
      float rndHlt = Math.RandomFloat( 0.50, 0.85 );
      itemEnt.SetHealth01( "", "", rndHlt );
    }
  }

  override void StartingEquipSetup( PlayerBase player, bool clothesChosen )
  {
    EntityAI itemClothing;
    EntityAI itemEnt;
    ItemBase itemBs;
    float rand;
    
    // top
    itemClothing = player.FindAttachmentBySlotName( "Body" );
    if ( itemClothing )
    {
      SetRandomHealth( itemClothing );

      itemEnt = itemClothing.GetInventory().CreateInInventory( "Rag" );
      if ( Class.CastTo( itemBs, itemEnt ) )
      {
        SetRandomHealth( itemEnt );
        itemBs.SetQuantity( 2 );
        itemBs.SetCleanness( 1 );
      }
      player.SetQuickBarEntityShortcut( itemEnt, 0 );

      string chemlightArray[] = { "Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red" };
      int rndIndex = Math.RandomInt( 0, 4 );
      itemEnt = itemClothing.GetInventory().CreateInInventory( chemlightArray[rndIndex] );
      SetRandomHealth( itemEnt );
      player.SetQuickBarEntityShortcut(itemEnt, 1);
      
    }

    // pants
    itemClothing = player.FindAttachmentBySlotName( "Legs" );
    if ( itemClothing )
    {
      SetRandomHealth( itemClothing );

      itemEnt = itemClothing.GetInventory().CreateInInventory( "Heatpack" );
      SetRandomHealth( itemEnt );
      
    }

    // shoes
    itemClothing = player.FindAttachmentBySlotName( "Feet" );
    if ( itemClothing )
    {
      SetRandomHealth( itemClothing );
    }

    player.GetStatWater().Set( 900 );
    player.GetStatEnergy().Set( 1100 );

    player.SetTemporaryResistanceToAgent(eAgents.INFLUENZA, 900);
  }
};


  
Mission CreateCustomMission(string path)
{
  return new CustomMission();
};