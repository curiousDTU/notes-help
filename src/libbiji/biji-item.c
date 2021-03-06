/*
 * biji-item.c
 *
 * Copyright 2013 Pierre-Yves Luyten <py@luyten.fr>
 *
 * Bijiben is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * bijiben is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "biji-item.h"
#include "biji-note-book.h"

/* Properties */
enum {
  PROP_0,
  PROP_BOOK,
  BIJI_ITEM_PROP
};


static GParamSpec *properties[BIJI_ITEM_PROP] = { NULL, };


struct BijiItemPrivate_
{
  BijiNoteBook *book;
};

static void biji_item_finalize (GObject *object);

G_DEFINE_TYPE (BijiItem, biji_item, G_TYPE_OBJECT)


static void
biji_item_set_property (GObject      *object,
                        guint         property_id,
                        const GValue *value,
                        GParamSpec   *pspec)
{
  BijiItem *self = BIJI_ITEM (object);


  switch (property_id)
    {
    case PROP_BOOK:
      self->priv->book = g_value_dup_object (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}


static void
biji_item_get_property (GObject    *object,
                        guint       property_id,
                        GValue     *value,
                        GParamSpec *pspec)
{
  BijiItem *self = BIJI_ITEM (object);

  switch (property_id)
    {
    case PROP_BOOK:
      g_value_set_object (value, self->priv->book);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
biji_item_class_init (BijiItemClass *klass)
{
  GObjectClass *g_object_class;

  g_object_class = G_OBJECT_CLASS (klass);

  g_object_class->get_property = biji_item_get_property;
  g_object_class->set_property = biji_item_set_property;
  g_object_class->finalize = biji_item_finalize;

  properties[PROP_BOOK] =
    g_param_spec_object("note-book",
                        "Note Book",
                        "The Note Book controlling this item",
                        BIJI_TYPE_NOTE_BOOK,
                        G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY);

  g_object_class_install_properties (g_object_class, BIJI_ITEM_PROP, properties);

  g_type_class_add_private ((gpointer)klass, sizeof (BijiItemPrivate));
}


static void
biji_item_finalize (GObject *object)
{
  g_return_if_fail (BIJI_IS_ITEM (object));

  G_OBJECT_CLASS (biji_item_parent_class)->finalize (object);
}


static void
biji_item_init (BijiItem *self)
{
  self->priv = G_TYPE_INSTANCE_GET_PRIVATE (self, BIJI_TYPE_ITEM, BijiItemPrivate);
  self->priv->book = NULL;
}

const gchar *
biji_item_get_title         (BijiItem *item)
{
  return BIJI_ITEM_GET_CLASS (item)->get_title (item);
}

const gchar *
biji_item_get_uuid          (BijiItem *item)
{
  return BIJI_ITEM_GET_CLASS (item)->get_uuid (item);
}


gpointer
biji_item_get_book     (BijiItem *item)
{
  return item->priv->book;
}


GdkPixbuf *
biji_item_get_icon          (BijiItem *item)
{
  return BIJI_ITEM_GET_CLASS (item)->get_icon (item);
}

GdkPixbuf *
biji_item_get_emblem        (BijiItem *item)
{
  return BIJI_ITEM_GET_CLASS (item)->get_emblem (item);
}

GdkPixbuf *
biji_item_get_pristine        (BijiItem *item)
{
  return BIJI_ITEM_GET_CLASS (item)->get_pristine (item);
}



gint64
biji_item_get_mtime           (BijiItem *item)
{
  return BIJI_ITEM_GET_CLASS (item)->get_mtime (item);
}


gboolean
biji_item_has_color           (BijiItem *item)
{
  return BIJI_ITEM_GET_CLASS (item)->has_color (item);
}

gboolean
biji_item_trash               (BijiItem *item)
{
  return BIJI_ITEM_GET_CLASS (item)->trash (item);
}

gboolean
biji_item_is_collectable       (BijiItem *item)
{
  return BIJI_ITEM_GET_CLASS (item)->is_collectable (item);
}

gboolean
biji_item_has_collection      (BijiItem *item, gchar *coll)
{
  return BIJI_ITEM_GET_CLASS (item)->has_collection (item, coll);
}

gboolean         biji_item_add_collection      (BijiItem *item, BijiItem *coll, gchar *title)
{
  return BIJI_ITEM_GET_CLASS (item)->add_collection (item, coll, title);
}

gboolean         biji_item_remove_collection   (BijiItem *item, BijiItem *collection)
{
  return BIJI_ITEM_GET_CLASS (item)->remove_collection (item, collection);
}
