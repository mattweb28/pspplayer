// ----------------------------------------------------------------------------
// PSP Player Emulation Suite
// Copyright (C) 2006 Ben Vanik (noxa)
// Licensed under the LGPL - see License.txt in the project root for details
// ----------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Text;

using Noxa.Emulation.Psp.Media;

namespace Noxa.Emulation.Psp.Games
{
	/// <summary>
	/// Describes the type of game.
	/// </summary>
	public enum GameType
	{
		/// <summary>
		/// Eboot as loaded off of a Memory Stick.
		/// </summary>
		Eboot,

		/// <summary>
		/// Retail UMD game.
		/// </summary>
		UmdGame
	}

	/// <summary>
	/// Describes the game category.
	/// </summary>
	public enum GameCategory
	{
		/// <summary>
		/// A gameshare game (WG).
		/// </summary>
		WlanGame,
		/// <summary>
		/// Save game data (MS).
		/// </summary>
		SaveGame,
		/// <summary>
		/// A Memory Stick game in the form of an EBOOT (MG).
		/// </summary>
		MemoryStickGame,
		/// <summary>
		/// A retail UMD game (UG).
		/// </summary>
		UmdGame,
		/// <summary>
		/// A UMD video title (UV).
		/// </summary>
		UmdVideo,
		/// <summary>
		/// A UMD audio title (UA).
		/// </summary>
		UmdAudio,
		/// <summary>
		/// A UMD cleaning disc (UC).
		/// </summary>
		CleaningDisc,
	}
	
	/// <summary>
	/// Game parameters.
	/// </summary>
	[Serializable]
	public class GameParameters : ICloneable
	{
		/// <summary>
		/// The category the game falls in to.
		/// </summary>
		public GameCategory Category = GameCategory.MemoryStickGame;

		/// <summary>
		/// The region the game is assigned to.
		/// </summary>
		public int Region = -1;

		/// <summary>
		/// The title of the game.
		/// </summary>
		public string Title = "Unknown";

		/// <summary>
		/// The ID of the game title.
		/// </summary>
		public string DiscID = null;

		/// <summary>
		/// The version of the game.
		/// </summary>
		public Version GameVersion = new Version();

		/// <summary>
		/// The system version required by the game.
		/// </summary>
		public Version SystemVersion = new Version();

		/// <summary>
		/// The language of the game.
		/// </summary>
		public string Language = null;

		/// <summary>
		/// Create a copy of the <see cref="GameParameters"/> instance.
		/// </summary>
		/// <returns>A copy of the <see cref="GameParameters"/> instance.</returns>
		public object Clone()
		{
			GameParameters p = new GameParameters();
			p.Category = this.Category;
			p.DiscID = this.DiscID;
			p.GameVersion = this.GameVersion;
			p.Language = this.Language;
			p.Region = this.Region;
			p.SystemVersion = this.SystemVersion;
			p.Title = this.Title;
			return p;
		}
	}

	/// <summary>
	/// Game information.
	/// </summary>
	[Serializable]
	public class GameInformation : IDisposable, ICloneable
	{
		/// <summary>
		/// The game type.
		/// </summary>
		public readonly GameType GameType;

		/// <summary>
		/// The unique ID of the UMD.
		/// </summary>
		public readonly string UniqueID;

		/// <summary>
		/// Game parameters.
		/// </summary>
		public readonly GameParameters Parameters;

		/// <summary>
		/// Game icon image.
		/// </summary>
		public readonly Stream Icon;

		/// <summary>
		/// Game background image.
		/// </summary>
		public readonly Stream Background;

		/// <summary>
		/// Folder where the game is located.
		/// </summary>
		[NonSerialized]
		public IMediaFolder Folder;

		/// <summary>
		/// The DATA.PSP entry.
		/// </summary>
		public Stream DataPsp;

		/// <summary>
		/// Path of the game on the host, if available.
		/// </summary>
		public string HostPath;

		/// <summary>
		/// For serialization. Do not use.
		/// </summary>
		public GameInformation()
		{
		}

		internal GameInformation( GameType gameType, IMediaFolder folder, GameParameters parameters, Stream icon, Stream background, string uniqueId )
		{
			this.GameType = gameType;
			this.UniqueID = uniqueId;
			this.Parameters = parameters;
			this.Icon = icon;
			this.Background = background;

			this.Folder = folder;
		}

		/// <summary>
		/// Release the resources used by the current <see cref="GameInformation"/> instance.
		/// </summary>
		~GameInformation()
		{
			GC.SuppressFinalize( this );
			this.Dispose();
		}

		#region IDisposable Members

		/// <summary>
		/// Release the resources used by the current <see cref="GameInformation"/> instance.
		/// </summary>
		public void Dispose()
		{
			if( IgnoreDispose == true )
				return;

			if( this.DataPsp != null )
				this.DataPsp.Dispose();
			this.DataPsp = null;

			if( this.Icon != null )
				this.Icon.Dispose();

			if( this.Background != null )
				this.Background.Dispose();

			this.Folder = null;
		}

		#endregion

		/// <summary>
		/// Ignore game in listings.
		/// </summary>
		[NonSerialized]
		public bool Ignore = false;

		/// <summary>
		/// Ignore Dispose calls; for internal use only.
		/// </summary>
		[NonSerialized]
		public bool IgnoreDispose = false;

		/// <summary>
		/// Create a copy of the <see cref="GameInformation"/> instance.
		/// </summary>
		/// <returns>A copy of the <see cref="GameInformation"/> instance.</returns>
		public object Clone()
		{
			GameInformation g = new GameInformation( this.GameType, null, ( GameParameters )this.Parameters.Clone(), null, null, this.UniqueID );
			g.HostPath = this.HostPath;
			return g;
		}
	}
}
